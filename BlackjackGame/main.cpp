#include "BlackjackGame.h"
#include <string>
#define NOMINMAX
#include <Windows.h>

void startGame(int& balance) {
    std::cout << "Starting a game of Blackjack!" << std::endl;

    while (true) {
        std::cout << "Please input your starting balance: ";
        std::cin >> balance;
        if (std::cin.fail() || balance < 1) {
            std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a positive number (minimum 1): " << std::endl;
        }
        else {
            break;
        }
    }
    std::cout << "Your starting balance: " << balance << std::endl;
}

bool placeBet(int& balance, int& bet) {
    std::cout << "Enter your bet (1, 2, 5, 10, 20, 50, 100), or type 'cashout' to exit: ";
    std::string input;
    while (true) {
        std::cin >> input;
        if (input == "cashout") {
            std::cout << "You cashed out with a balance of: " << balance << std::endl;
            std::cout << "Exiting the game..." << std::endl;
            return false;
        }
        try {
            bet = std::stoi(input);
        }
        catch (...) {
            std::cout << "Invalid input. Please enter a valid bet amount: ";
            continue;
        }
        if (bet > balance) {
            std::cout << "You cannot bet more than your balance! Enter a new bet: ";
        }
        else if (bet <= 0 || (bet != 1 && bet != 2 && bet != 5 && bet != 10 && bet != 20 && bet != 50 && bet != 100)) {
            std::cout << "Invalid bet amount. Please enter one of (1, 2, 5, 10, 20, 50, 100): ";
        }
        else {
            balance -= bet;
            return true;
        }
    }
}

void dealCards(std::vector<Card>& deck, std::vector<Card>& playerHand, std::vector<Card>& dealerHand) {
	playerHand.push_back(deck.back()); deck.pop_back();
	dealerHand.push_back(deck.back()); deck.pop_back();
	playerHand.push_back(deck.back()); deck.pop_back();
	dealerHand.push_back(deck.back()); deck.pop_back();
    std::cout << "Your hand: " << displayHand(playerHand, true) << std::endl;
    std::cout << "Your hand total: " << calculateSum(playerHand) << std::endl;
    std::cout << "Dealer's visible card: " << displayHand(dealerHand, false) << std::endl;
    std::cout << "Dealer's hand total: " << cardValue(dealerHand[0]) << std::endl;
}

bool playerTurn(std::vector<Card>& playerHand, std::vector<Card>& deck) {
    while (true) {
        std::cout << "Would you like to 'hit' (h) or 'stand' (s)? ";
        std::string choice;
        std::cin >> choice;

        if (choice == "h" || choice == "H") {
            playerHand.push_back(deck.back());
            deck.pop_back();
            std::cout << "Your hand: " << displayHand(playerHand, true) << std::endl;
            std::cout << "Your hand total: " << calculateSum(playerHand) << std::endl;

            if (calculateSum(playerHand) > 21) {
                std::cout << "You busted! You lose your bet.\n";
                return false;
            }
        }
        else if (choice == "s" || choice == "S") {
            return true;
        }
        else {
            std::cout << "Invalid input. Please enter 'h' for hit or 's' for stand." << std::endl;
        }
    }
}

void gameResult(int playerSum, int dealerSum, int bet, int& balance) {
    std::cout << "Final scores:\n";
    std::cout << "Player: " << playerSum << std::endl;
    std::cout << "Dealer: " << dealerSum << std::endl;
    if (dealerSum > 21) {
        std::cout << "Dealer busted! You win!\n";
        balance += bet * 2;
    }
    else if (playerSum > 21) {
        std::cout << "You busted! You lose your bet.\n";
    }
    else if (playerSum > dealerSum) {
        std::cout << "You win! You gain your bet.\n";
        balance += bet * 2;
    }
    else if (playerSum < dealerSum) {
        std::cout << "Dealer wins! You lose your bet.\n";
    }
    else {
        std::cout << "It's a tie! You get your bet back.\n";
        balance += bet;
    }
    std::cout << "Your new balance: " << balance << std::endl;
}

int main() {
	SetConsoleOutputCP(CP_UTF8);
    int balance = 0, bet = 0;
    startGame(balance);
    while (balance >= 1) {
        if (!placeBet(balance, bet)) break;
        std::vector<Card> deck = createDeck();
        std::vector<Card> playerHand, dealerHand;

        dealCards(deck, playerHand, dealerHand);
        int playerSum = calculateSum(playerHand);

        if (playerSum == 21) {
            std::cout << "You have a Blackjack!" << std::endl;
            dealerTurn(dealerHand, deck);
            gameResult(playerSum, calculateSum(dealerHand), bet, balance);
            continue;
        }

        if (!playerTurn(playerHand, deck)) {
            std::cout << "Your new balance: " << balance << std::endl;
            if (balance < 1) {
                std::cout << "You have no money left. Game over!" << std::endl;
                break;
            }
            continue;
        }
        std::cout << "Dealer's turn..\n";
        dealerTurn(dealerHand, deck);
        std::cout << "Dealer's hand: " << displayHand(dealerHand, true) << std::endl;

        gameResult(calculateSum(playerHand), calculateSum(dealerHand), bet, balance);

        if (balance < 1) {
            std::cout << "You have no money left. Game over!" << std::endl;
            break;
        }
    }
    return 0;
}