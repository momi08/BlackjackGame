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
    std::vector<std::string> names = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
    for (const std::string& name : names) {
        for (int i = 0; i < 4; ++i) {
            int value = (name == "J" || name == "Q" || name == "K") ? 10 : (name == "A" ? 11 : stoi(name));
            deck.push_back({ name, value });
        }
    }
    std::random_device rd;
    std::default_random_engine rng(rd()); 
    shuffle(deck.begin(), deck.end(), rng); 
    return deck;
}

int calculateSum(const std::vector<Card>& hand) {
    int sum = 0;
    int aceCount = 0;
    for (const Card& card : hand) {
        if (card.cardName == "A") {
            aceCount++;
        }
        else {
            sum += card.cardValue;
        }
    }
    for (int i = 0; i < aceCount; ++i) {
        if (sum + 11 <= 21) {
            sum += 11;
        }
        else {
            sum += 1;
        }
    }
    return sum;
}

bool getValidBalance(std::istream& is, int& balance) {
    while (true) {
        std::cout << "Please input your starting balance: ";
        if (is >> balance && balance > 0) {
            return true;
        }
        else {
            std::cout << "Invalid input! Please enter a valid positive number for the balance." << std::endl;
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

bool getValidBet(std::istream& is, int& bet, int balance) {
    std::string input;
    while (true) {
        std::cout << "Enter your bet (1, 2, 5, 10, 20, 50, 100), or type 'cashout' to exit: ";
        is >> input;

        if (input == "cashout") {
            return false;
        }
        try {
            bet = std::stoi(input);
            std::vector<int> validBets = { 1, 2, 5, 10, 20, 50, 100 };
            if (std::find(validBets.begin(), validBets.end(), bet) != validBets.end() && bet <= balance) {
                return true;
            }
        }
        catch (...) {
        }
        std::cout << "Invalid bet! Please enter a valid bet (1, 2, 5, 10, 20, 50, 100) or 'cashout'.\n";
        is.clear();
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void displayHand(const std::vector<Card>& hand) {
    for (const Card& card : hand) {
        std::cout << card.cardName << " ";
    }
    std::cout << std::endl;
}

void playerTurn(std::vector<Card>& playerHand, std::vector<Card>& deck) {
    while (true) {
        int sum = calculateSum(playerHand);
        displayHand(playerHand);
        std::cout << "Your total: " << sum << std::endl;
        if (sum == 21) {
            std::cout << "You have Blackjack!\n";
            delay(1);
            return;
        }
        if (sum > 21) {
            delay(1);
            return;
        }
        std::cout << "Do you want to (h)it or (s)tand? ";
        char choice;
        std::cin >> choice;

        if (choice == 'h' || choice == 'H') {
            playerHand.push_back(deck.back());
            deck.pop_back();
        }
        else if (choice == 's' || choice == 'S') {
            break;
        }
        else {
            std::cout << "Invalid choice, please choose 'h' or 's'.\n";
        }
    }
}

void dealerTurn(std::vector<Card>& dealerHand, std:: vector<Card>& deck) {
    while (calculateSum(dealerHand) < 17) {
        dealerHand.push_back(deck.back());
        deck.pop_back();
        displayHand(dealerHand);
        int sum = calculateSum(dealerHand);
        std::cout << "Dealer's total: " << sum << std::endl;
        delay(1);
        if (sum > 21) {
            std::cout << "Dealer busts! Over 21." << std::endl;
            return;
        }
    }
    std::cout << "Dealer stands at " << calculateSum(dealerHand) << std::endl;
    delay(1);
}
