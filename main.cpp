#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

class Holders {
public:
    std::vector<std::string> cards;
    std::vector<int> values;
    int points = 0;

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
    std::vector<std::string> deck;

    for (int i = 0; i < 13; ++i) {
        for (int j = 0; j < 4; ++j) {
            deck.push_back(values[i] + suits[j]);
        }
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle (deck.begin(), deck.end(), std::default_random_engine(seed));

    for (const auto& card : deck) {
        std::cout << card << " ";
    }
    std::cout << std::endl << endl;

    Holders dealer;
    Holders player;
    int dealer_Ace = 0;
    int player_Ace = 0;
    dealer.cards.push_back(deck.front());
    dealer.points += GetPoints(deck.front(),dealer_Ace);
    deck.erase(deck.begin());

    player.cards.push_back(deck.front());
    player.points += GetPoints(deck.front(),player_Ace);
    deck.erase(deck.begin());

    dealer.cards.push_back(deck.front());
    dealer.points += GetPoints(deck.front(),dealer_Ace);
    deck.erase(deck.begin());

    player.cards.push_back(deck.front());
    player.points += GetPoints(deck.front(),player_Ace);
    deck.erase(deck.begin());
//
//    cout << dealer.points << endl;
//    cout << player.points << endl;


    while (player.points < 17 ) {
        player.cards.push_back(deck.front());
        player.points += GetPoints(deck.front(),player_Ace);
        deck.erase(deck.begin());

        if (player.points > 21 && player_Ace > 0) {
            player.points -= 10;
            player_Ace -= 1;
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

    cout << "Player" << endl;
    for (const auto& card : player.cards) {
        std::cout << card << " ";
    }
    cout << endl;
    cout << player.points << endl;

    cout << endl << "Dealer" << endl;
    for (const auto& card : dealer.cards) {
        std::cout << card << " ";
    }
    cout << endl;
    cout << dealer.points << endl;


    return 0;
}
