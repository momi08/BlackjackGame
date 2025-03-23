#pragma once
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <iostream>
#include <limits>

struct Card {
    std::string cardName;
    int cardValue;
};

std::vector<Card> createDeck();
int calculateSum(const std::vector<Card>& hand);
bool getValidBet(std::istream& is, int& bet, int balance);
bool getValidBalance(std::istream& is, int& balance);
void displayHand(const std::vector<Card>& hand);
void playerTurn(std::vector<Card>& playerHand, std::vector<Card>& deck);
void dealerTurn(std::vector<Card>& dealerHand, std::vector<Card>& deck);
