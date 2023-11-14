#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <map>
#include <set>

using namespace std;

class Holders {
public:
    std::vector<std::string> cards;
    std::vector<int> values;
    int points = 0;
    int card_1 = 0;
    int card_2 = 0;

};

int GetPoints(string card, int num_of_ace) {
    string card_value = card.substr(0, card.size() - 1);
    if (card_value == "J" || card_value == "Q" ||card_value == "K") {
        return 10;
    }
    else if (card_value == "A") {
        num_of_ace += 1;
        return 11;
    }
    else {
        return std::stoi(card_value);
    }

}


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
    int HardTotal[10][10] = {
            {hit,hit,hit,hit,hit,hit,hit,hit,hit,hit},
            {hit,double_down_hit,double_down_hit,double_down_hit,double_down_hit,hit,hit,hit,hit,hit},
            {double_down_hit,double_down_hit,double_down_hit,double_down_hit,double_down_hit,double_down_hit,double_down_hit,double_down_hit,hit,hit},
            {double_down_hit,double_down_hit,double_down_hit,double_down_hit,double_down_hit,double_down_hit,double_down_hit,double_down_hit,double_down_hit,double_down_hit},
            {hit,hit,stand,stand,stand,hit,hit,hit,hit,hit},
            {stand,stand,stand,stand,stand,hit,hit,hit,hit,hit},
            {stand,stand,stand,stand,stand,hit,hit,hit,hit,hit},
            {stand,stand,stand,stand,stand,hit,hit,hit,hit,hit},
            {stand,stand,stand,stand,stand,hit,hit,hit,hit,hit},
            {stand,stand,stand,stand,stand,stand,stand,stand,stand,stand},
            };




    long int num_elems = 10'000'000;
    long int wins = 0;
    long int draws = 0;
    long int loss = 0;

    for (int b =0 ; b < num_elems; ++b){
        std::vector<std::string> deck;
        for (int i = 0; i < 13; ++i) {
            for (int j = 0; j < 4; ++j) {
                deck.push_back(values[i] + suits[j]);
            }
        }



        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));

//        for (const auto& card : deck) {
//            std::cout << card << " ";
//        }
//        std::cout << std::endl << endl;

        Holders dealer;
        Holders player;

        int dealer_Ace = 0;
        int player_Ace = 0;
        string dealer_face_card = deck.front();
        // ASSIGN CARDS
        dealer.cards.push_back(deck.front());
        dealer.points += GetPoints(deck.front(), dealer_Ace);
        dealer.card_1 += GetPoints(deck.front(), 0);
        deck.erase(deck.begin());

        player.cards.push_back(deck.front());
        player.points += GetPoints(deck.front(), player_Ace);
        player.card_1 += GetPoints(deck.front(), 0);
        deck.erase(deck.begin());

        dealer.cards.push_back(deck.front());
        dealer.points += GetPoints(deck.front(), dealer_Ace);
        deck.erase(deck.begin());

        player.cards.push_back(deck.front());
        player.points += GetPoints(deck.front(), player_Ace);
        player.card_2 += GetPoints(deck.front(), 0);
        deck.erase(deck.begin());

        // SPLIT OR NOT
//    player.card_1 = 2;
//    player.card_2 = 2;
//    dealer.card_1 = 7;
//    if (player.card_1 == player.card_2) {
//        cout << "Rule: " << DouleRule[11 - player.card_1][dealer.card_1-2] << endl;
//    }
//


        // PLAYER
        bool stand_bool = false;
        while (player.points <= 17 && !stand_bool) {
            //        int stand = 1;
            //        int hit = 2;
            //        int double_down_hit = 5;
            int action = 0;
            if (player.points >= 8) {
                action = HardTotal[player.points - 8][dealer.card_1 - 2];
            }
            if (action == 1) {
                stand_bool = true;
            }
            else if (action == 2) {
                player.cards.push_back(deck.front());
                    player.points += GetPoints(deck.front(), player_Ace);
                    deck.erase(deck.begin());
                    if (player.points > 21 && player_Ace > 0) {
                        player.points -= 10;
                        player_Ace -= 1;
                    }
            }
            else if (action == 5) {
                player.cards.push_back(deck.front());
                player.points += GetPoints(deck.front(), player_Ace);
                deck.erase(deck.begin());
                if (player.points > 21 && player_Ace > 0) {
                    player.points -= 10;
                    player_Ace -= 1;
                }
            }
            else  {
                player.cards.push_back(deck.front());
                player.points += GetPoints(deck.front(), player_Ace);
                deck.erase(deck.begin());
                if (player.points > 21 && player_Ace > 0) {
                    player.points -= 10;
                    player_Ace -= 1;
                }
            }

        }

        while (dealer.points < 17 ) {
            dealer.cards.push_back(deck.front());
            dealer.points += GetPoints(deck.front(),dealer_Ace);
            deck.erase(deck.begin());

            if (dealer.points > 21 && player_Ace > 0) {
                dealer.points -= 10;
                dealer_Ace -= 1;
            }
        }
//        cout << "p: " <<player.points << endl << dealer.points << endl;
        if (player.points <= 21 && (dealer.points < player.points || dealer.points > 21) ) {
//            cout << "W"<<endl;
            ++wins;
        }
        else if ((player.points == dealer.points) || (player.points > 21 && dealer.points > 21) ) {
//            cout << "D"<<endl;

            ++draws;
        }
        else if (dealer.points <= 21 && (player.points < dealer.points || player.points > 21)) {
//            cout << "l"<<endl;

            ++loss;
        }
        else {
            cout << "Something Else" << endl;
        }

    }
    cout << "Wins: " << static_cast<double>(wins) / num_elems << endl;
    cout << "Draws: "<<  static_cast<double>(draws) / num_elems << endl;
    cout << "Loss: "<<  static_cast<double>(loss) / num_elems<< endl;
    return 0;
}
