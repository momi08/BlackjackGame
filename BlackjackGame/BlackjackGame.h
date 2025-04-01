#pragma once
#include <vector>
#include <iostream>

enum class Suit { Hearts, Diamonds, Clubs, Spades };
enum class Rank {
    Two = 2, Three, Four, Five, Six, Seven, Eight, Nine, Ten,
    Jack, Queen, King, Ace
};

struct Card {
    Rank rank;
    Suit suit;
    Card(Rank r, Suit s) : rank(r), suit(s) {}
};

int cardValue(const Card& card);
std::vector<Card> createDeck();
int calculateSum(const std::vector<Card>& hand);
bool getBet(std::istream& is, int& bet, int balance);
bool validateBet(int bet, int balance);
bool getValidBalance(std::istream& is, int& balance);
std::string displayHand(const std::vector<Card>& hand, bool showAll);
std::string cardToString(const Card& card);
bool playerTurn(std::vector<Card>& playerHand, std::vector<Card>& deck, std::istream& input);
bool dealerTurn(std::vector<Card>& dealerHand, std::vector<Card>& deck);
