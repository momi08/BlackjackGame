#include "BlackjackGame.h"
#include <random>
#include <sstream>
#include <array>

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

std::string cardToString(const Card& card) {
    static const std::array<std::string, 13> rankNames = {
        "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"
    };
    static const std::array<std::string, 4> suitSymbols = {
        "\xE2\x99\xA5",
        "\xE2\x99\xA6",
        "\xE2\x99\xA3",
        "\xE2\x99\xA0"
    };
    return rankNames[static_cast<int>(card.rank) - 2] + suitSymbols[static_cast<int>(card.suit)];
}

std::string displayHand(const std::vector<Card>& hand, bool showAll) {
    std::ostringstream output;
    if (showAll) {
        for (size_t i = 0; i < hand.size(); ++i) {
            output << cardToString(hand[i]);
            if (i != hand.size() - 1) {
                output << " ";
            }
        }
    }
    else {
        if (!hand.empty()) {
            output << cardToString(hand[0]);
        }
    }
    return output.str();
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

bool playerTurn(std::vector<Card>& playerHand, std::vector<Card>& deck, std::istream& input) {
    while (true) {
        int sum = calculateSum(playerHand);
        if (sum >= 21) return (sum == 21);

        char choice;
        input >> choice;
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
    return (calculateSum(dealerHand) > 21);
}
