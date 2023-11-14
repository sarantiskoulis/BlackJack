//
// Created by sarantis on 14/11/2023.
//

#ifndef BLACKJACK_MISC_H
#define BLACKJACK_MISC_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>


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


int GetPoints(std::string card);
int BlackJackScore(std::vector<std::string>& deck, Holders& suit, int dealer_card);

#endif //BLACKJACK_MISC_H
