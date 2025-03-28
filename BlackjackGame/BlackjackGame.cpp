#include "BlackjackGame.h"
#include <random>
#include <chrono>
#include <thread>
#include <sstream>

void delay(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

std::vector<Card> createDeck() {
    std::vector<Card> deck;
    for (int suit = 0; suit < 4; ++suit) {
        for (int rank = 2; rank <= 14; ++rank) {
            deck.push_back({ static_cast<Rank>(rank), static_cast<Suit>(suit) });
        }
    }
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(deck.begin(), deck.end(), rng);
    return deck;
}

int cardValue(const Card& card) {
    if (card.rank == Rank::Jack || card.rank == Rank::Queen || card.rank == Rank::King) {
        return 10;
    }
    else if (card.rank == Rank::Ace) {
        return 11;
    }
    else {
        return static_cast<int>(card.rank);
    }
}

int calculateSum(const std::vector<Card>& hand) {
    int sum = 0;
    int aceCount = 0;
    for (const Card& card : hand) {
        sum += cardValue(card);
        if (card.rank == Rank::Ace) {
            aceCount++;
        }
    }
    while (sum > 21 && aceCount > 0) {
        sum -= 10;
        aceCount--;
    }
    return sum;
}

void displayHand(const std::vector<Card>& hand, bool showAll) {
    if (showAll) {
        for (const Card& card : hand) {
            std::string rankStr;
            switch (card.rank) {
            case Rank::Two: rankStr = "2"; break;
            case Rank::Three: rankStr = "3"; break;
            case Rank::Four: rankStr = "4"; break;
            case Rank::Five: rankStr = "5"; break;
            case Rank::Six: rankStr = "6"; break;
            case Rank::Seven: rankStr = "7"; break;
            case Rank::Eight: rankStr = "8"; break;
            case Rank::Nine: rankStr = "9"; break;
            case Rank::Ten: rankStr = "10"; break;
            case Rank::Jack: rankStr = "J"; break;
            case Rank::Queen: rankStr = "Q"; break;
            case Rank::King: rankStr = "K"; break;
            case Rank::Ace: rankStr = "A"; break;
            }
            std::string suitStr;
            switch (card.suit) {
            case Suit::Hearts: suitStr = "Hearts"; break;
            case Suit::Diamonds: suitStr = "Diamonds"; break;
            case Suit::Clubs: suitStr = "Clubs"; break;
            case Suit::Spades: suitStr = "Spades"; break;
            }
            std::cout << rankStr << " of " << suitStr << "  ";
        }
    }
    else {
        if (!hand.empty()) {
            const Card& card = hand[0];
            std::string rankStr;
            switch (card.rank) {
            case Rank::Two: rankStr = "2"; break;
            case Rank::Three: rankStr = "3"; break;
            case Rank::Four: rankStr = "4"; break;
            case Rank::Five: rankStr = "5"; break;
            case Rank::Six: rankStr = "6"; break;
            case Rank::Seven: rankStr = "7"; break;
            case Rank::Eight: rankStr = "8"; break;
            case Rank::Nine: rankStr = "9"; break;
            case Rank::Ten: rankStr = "10"; break;
            case Rank::Jack: rankStr = "J"; break;
            case Rank::Queen: rankStr = "Q"; break;
            case Rank::King: rankStr = "K"; break;
            case Rank::Ace: rankStr = "A"; break;
            }
            std::string suitStr;
            switch (card.suit) {
            case Suit::Hearts: suitStr = "Hearts"; break;
            case Suit::Diamonds: suitStr = "Diamonds"; break;
            case Suit::Clubs: suitStr = "Clubs"; break;
            case Suit::Spades: suitStr = "Spades"; break;
            }
            std::cout << rankStr << " of " << suitStr << "  ";
        }
    }
    std::cout << std::endl;
}

bool getValidBalance(std::istream& is, int& balance) {
    return (is >> balance && balance > 0);
}

bool validateBet(int bet, int balance) {
    std::vector<int> validBets = { 1, 2, 5, 10, 20, 50, 100 };
    return (std::find(validBets.begin(), validBets.end(), bet) != validBets.end() && bet <= balance);
}

bool getBet(std::istream& is, int& bet, int balance) {
    std::string input;
    if (!(is >> input)) return false;
    if (input == "cashout") return false;

    try {
        bet = std::stoi(input);
        return validateBet(bet, balance);
    }
    catch (...) {
        return false;
    }
}

bool playerTurn(std::vector<Card>& playerHand, std::vector<Card>& deck) {
    while (true) {
        int sum = calculateSum(playerHand);
        if (sum >= 21) return (sum == 21); 

        char choice;
        std::cin >> choice;
        if (choice == 'h' || choice == 'H') {
            playerHand.push_back(deck.back());
            deck.pop_back();
        }
        else if (choice == 's' || choice == 'S') {
            return false;
        }
    }
}

bool dealerTurn(std::vector<Card>& dealerHand, std::vector<Card>& deck) {
    while (calculateSum(dealerHand) < 17) {
        dealerHand.push_back(deck.back());
        deck.pop_back();
    }
    displayHand(dealerHand, true);
    return (calculateSum(dealerHand) > 21);
}
