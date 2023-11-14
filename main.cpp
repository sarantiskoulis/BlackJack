#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "misc.h"


using namespace std;

//class Holders {
//public:
//    std::vector<std::string> cards;
//    std::vector<int> values;
//    int points = 0;
//    int card_1 = 0;
//    int card_2 = 0;
//    int num_Ace = 0;
//    void AddPoint(int point, int card) {
//        points += point;
//        if (card == 1) {
//            card_1 = point;
//        }
//        else if (card == 2) {
//            card_2 = point;
//        }
//
//        if (point == 11) {
//            ++num_Ace;
//        }
//    }
//};


//int GetPoints(string card) {
//    string card_value = card.substr(0, card.size() - 1);
//    if (card_value == "J" || card_value == "Q" ||card_value == "K") {
//        return 10;
//    }
//    else if (card_value == "A") {
//        return 11;
//    }
//    else {
//        return std::stoi(card_value);
//    }
//
//}


int main() {
    string values[13] = {"2", "3","4", "5", "6","7", "8", "9", "10", "J", "Q", "K",  "A"};
    string suits[4] = {"H", "D", "C" , "S"};

    int ignore = 0;
    int stand = 1;
    int hit = 2;
    int double_down = 3;
    int double_down_double = 4;
    int double_down_hit = 5;
    int DouleRule[10][10] = {
            {double_down,double_down,double_down,double_down,double_down,double_down,double_down,double_down,double_down,double_down},
            {ignore,ignore,ignore,ignore,ignore,ignore,ignore,ignore,ignore,ignore},
            {double_down,double_down,double_down,double_down,double_down,ignore,double_down,double_down,ignore,ignore},
            {double_down,double_down,double_down,double_down,double_down,double_down,double_down,double_down,double_down,double_down},
            {double_down,double_down,double_down,double_down,double_down,double_down,ignore,ignore,ignore,ignore},
            {double_down_double,double_down,double_down,double_down,double_down,ignore,ignore,ignore,ignore,ignore},
            {ignore,ignore,ignore,ignore,ignore,ignore,ignore,ignore,ignore,ignore},
            {ignore,ignore,ignore,double_down_double,double_down_double,ignore,ignore,ignore,ignore,ignore},
            {double_down_double,double_down_double,double_down,double_down,double_down,double_down,ignore, ignore, ignore, ignore},
            {double_down_double,double_down_double,double_down,double_down,double_down,double_down,ignore, ignore, ignore, ignore},
    };
    int SoftTotal[8][10] {
            {stand,stand,stand,stand,stand,stand,stand,stand,stand,stand},
            {stand,stand,stand,stand,double_down_hit,stand,stand,stand,stand,stand},
            {double_down_hit,double_down_hit,double_down_hit,double_down_hit,double_down_hit,stand,stand,hit,hit,hit},
            {hit,double_down,double_down,double_down,double_down,hit,hit,hit,hit,hit},
            {hit,hit,double_down,double_down,double_down,hit,hit,hit,hit,hit},
            {hit,hit,double_down,double_down,double_down,hit,hit,hit,hit,hit},
            {hit,hit,hit,double_down,double_down,hit,hit,hit,hit,hit},
            {hit,hit,hit,double_down,double_down,hit,hit,hit,hit,hit},
    };




    long int num_elems = 1;
    long int wins = 0;
    long int draws = 0;
    long int loss = 0;

    for (int b =0 ; b < num_elems; ++b){

        // GET A NEW DECK
        std::vector<std::string> deck;
        for (int i = 0; i < 13; ++i) {
            for (int j = 0; j < 4; ++j) {
                deck.push_back(values[i] + suits[j]);
            }
        }
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));


        // DEALER CARDS
        Holders dealer;
        //PLAYER CARDS
        Holders player;

        string dealer_face_card = deck.front();
        // ASSIGN CARDS
        dealer.AddPoint(GetPoints(deck.front()), 1);
        deck.erase(deck.begin());

        player.AddPoint(GetPoints(deck.front()), 1);
        deck.erase(deck.begin());

        dealer.AddPoint(GetPoints(deck.front()), 2);
        deck.erase(deck.begin());

        player.AddPoint(GetPoints(deck.front()), 2);
        deck.erase(deck.begin());

        // SPLIT OR NOT
//        int ignore = 0;
//        int stand = 1;
//        int hit = 2;
//        int double_down = 3;
//        int double_down_double = 4;
//        int double_down_hit = 5;
    player.card_1 = 8;
    player.card_2 = 8;
    dealer.card_1 = 3;
    vector<Holders> Suits;
    bool cardHasSplit = false;
    if (player.card_1 == player.card_2) {
        int suit_aces[2] = {0,0};
        int rule = DouleRule[11 - player.card_1][dealer.card_1-2];
        cout << "Rule: " << rule << endl;
        if (rule == 3 || rule == 4) {
            Holders player_suit_1;
            Holders player_suit_2;
            player_suit_1.card_1 = player.card_1;
            player_suit_1.points += player.card_1;


            player_suit_2.card_1 = player.card_1;
            player_suit_2.card_1 += player.card_1;

            if (player.card_1 == 11) {
                suit_aces[0] += 1;
                suit_aces[1] += 1;
            };

            // GRAB A CARD FOR SUIT 1;
            player_suit_1.AddPoint(GetPoints(deck.front()), 2);
            deck.erase(deck.begin());
            Suits.push_back(player_suit_1);
            // GRAB A CARD FOR SUIT 2;
            player_suit_2.AddPoint(GetPoints(deck.front()), 2);
            deck.erase(deck.begin());
            Suits.push_back(player_suit_2);

            cardHasSplit = true;
        }

    }

        // PLAYER
    if (cardHasSplit) {
        for (auto& suit: Suits) {
            int points = BlackJackScore(deck,suit, dealer.card_1) ;
            cout << "Points " << points << endl;
        }
    }
    else {
        int points = BlackJackScore(deck,player, dealer.card_1);
//        cout << "Points normal : " << points << endl;
    }


        while (dealer.points < 17 ) {
            dealer.cards.push_back(deck.front());
            dealer.AddPoint(GetPoints(deck.front()), 0);
            deck.erase(deck.begin());

            if (dealer.points > 21 && dealer.num_Ace > 0) {
                dealer.points -= 10;
                dealer.num_Ace -= 1;
            }
        }
        cout<< "Dealer Points: " << dealer.points << endl;

        if (cardHasSplit) {
            for (auto& suit: Suits) {
                if (suit.points <= 21 && (dealer.points < suit.points || dealer.points > 21) ) {
                    ++wins;
                }
                else if ((suit.points == dealer.points) || (suit.points > 21 && dealer.points > 21) ) {

                    ++draws;
                }
                else if (dealer.points <= 21 && (suit.points < dealer.points || suit.points > 21)) {

                    ++loss;
                }
                else {
                    cout << "Something Else" << endl;
                }
            }
        }
        else {
            if (player.points <= 21 && (dealer.points < player.points || dealer.points > 21) ) {
                ++wins;
            }
            else if ((player.points == dealer.points) || (player.points > 21 && dealer.points > 21) ) {
                ++draws;
            }
            else if (dealer.points <= 21 && (player.points < dealer.points || player.points > 21)) {
                ++loss;
            }
            else {
                cout << "Something Else" << endl;
            }
        }


    }
    cout << "Wins: " << static_cast<double>(wins) / num_elems << endl;
    cout << "Draws: "<<  static_cast<double>(draws) / num_elems << endl;
    cout << "Loss: "<<  static_cast<double>(loss) / num_elems<< endl;
    return 0;
}
