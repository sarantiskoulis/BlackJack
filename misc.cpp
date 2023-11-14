//
// Created by sarantis on 14/11/2023.
//
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "misc.h"

using namespace std;
class Holders {
public:
    std::vector<std::string> cards;
    std::vector<int> values;
    int points = 0;
    int card_1 = 0;
    int card_2 = 0;
    int num_Ace = 0;
    void AddPoint(int point, int card) {
        points += point;
        if (card == 1) {
            card_1 = point;
        }
        else if (card == 2) {
            card_2 = point;
        }
        if (point == 11) {
            ++num_Ace;
        }
    }
};


int BlackJackScore(vector<string>& deck, Holders& suit, int dealer_card) {

    int stand = 1;
    int hit = 2;
    int double_down_hit = 5;
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


    bool stand_bool = false;

    while (suit.points <= 17 && !stand_bool) {
        //        int stand = 1;
        //        int hit = 2;
        //        int double_down_hit = 5;
        int action = 0;
        if (suit.points >= 8) {
            action = HardTotal[suit.points - 8][dealer_card - 2];
        }

        if (action == 1) {
            stand_bool = true;
        }
        else if (action == 2) {
            suit.cards.push_back(deck.front());
            suit.AddPoint(GetPoints(deck.front()), 0);
            deck.erase(deck.begin());
            if (suit.points > 21 && suit.num_Ace > 0) {
                suit.points -= 10;
                suit.num_Ace -= 1;
            }
        }
        else if (action == 5) {
            suit.cards.push_back(deck.front());
            suit.AddPoint(GetPoints(deck.front()), 0);
            deck.erase(deck.begin());
            if (suit.points > 21 && suit.num_Ace > 0) {
                suit.points -= 10;
                suit.num_Ace -= 1;
            }
        }
        else  {
            suit.cards.push_back(deck.front());
            suit.AddPoint(GetPoints(deck.front()), 0);
            deck.erase(deck.begin());
            if (suit.points > 21 && suit.num_Ace > 0) {
                suit.points -= 10;
                suit.num_Ace -= 1;
            }
        }

    }
    return suit.points;

}
