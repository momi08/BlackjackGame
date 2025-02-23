#define BLACKJACK_H
#pragma once
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <iostream>
#include <limits>

using namespace std;

struct Card {
    string cardName;
    int cardValue;
};

vector<Card> createDeck();
int calculateSum(const vector<Card>& hand);
bool getValidBet(int& bet, int balance);
bool getValidBalance(int& balance);
void displayHand(const vector<Card>& hand);
void playerTurn(vector<Card>& playerHand, vector<Card>& deck);
void dealerTurn(vector<Card>& dealerHand, vector<Card>& deck);

