#include "BlackjackGame.h"

int main() {
    int balance = 0;
    int bet = 0;

    std::cout << "Starting a game of Blackjack!" << std::endl;
    std::cout << "Please input your starting balance :" << std::endl;
    if (!getValidBalance(std::cin, balance)) {
        return 0;
    }
    std::cout << "Your starting balance: " << balance << std::endl;
    while (balance >= 1) {
        std::cout << "Enter your bet (1, 2, 5, 10, 20, 50, 100), or type 'cashout' to exit: ";
        if (!getBet(std::cin, bet, balance)) {
            std::cout << "You cashed out with a balance of: " << balance << std::endl;
            std::cout << "Exiting the game..." << std::endl;
            break;
        }
        balance -= bet;

        std::vector<Card> deck = createDeck();
        std::vector<Card> playerHand;
        std::vector<Card> dealerHand;

        playerHand.push_back(deck.back()); deck.pop_back();
        dealerHand.push_back(deck.back()); deck.pop_back();
        playerHand.push_back(deck.back()); deck.pop_back();
        dealerHand.push_back(deck.back()); deck.pop_back();

        std::cout << "Your hand: " << displayHand(playerHand, true) << std::endl;
        std::cout << "Your hand total: " << calculateSum(playerHand) << std::endl;
        std::cout << "Dealer's visible card: " << displayHand(dealerHand, false) << std::endl;
        std::cout << "Dealer's hand total: " << cardValue(dealerHand[0]) << std::endl;

        int playerSum = calculateSum(playerHand);
        if (playerSum == 21 && playerHand.size() == 2) {
            std::cout << "You have a Blackjack!" << std::endl;
            dealerTurn(dealerHand, deck);
            int dealerSum = calculateSum(dealerHand);

            std::cout << "Final scores:\n";
            std::cout << "Player: " << playerSum << std::endl;
            std::cout << "Dealer: " << dealerSum << std::endl;

            if (dealerSum == 21) {
                std::cout << "It's a tie! You get your bet back.\n";
                balance += bet;
            }
            else {
                std::cout << "You win! You gain your bet.\n";
                balance += bet * 2;
            }
            std::cout << "Your new balance: " << balance << std::endl;
            continue;
        }

        while (true) {
            std::cout << "Would you like to 'hit' (h) or 'stand' (s)? ";
            char choice;
            std::cin >> choice;

            if (choice == 'h' || choice == 'H') {
                playerHand.push_back(deck.back());
                deck.pop_back();      
                std::cout << displayHand(playerHand, true) << std::endl;
                playerSum = calculateSum(playerHand);
                std::cout << "Your hand total: " << playerSum << std::endl;

                if (playerSum == 21 && playerHand.size() >= 2) {
                    std::cout << "You have a Blackjack!\n";
                    break;
                }

                if (playerSum > 21) {
                    std::cout << "You busted! You lose your bet.\n";
                    std::cout << "Your new balance: " << balance << std::endl;
                    break;
                }
            }
            else if (choice == 's' || choice == 'S') {
                break;
            }
            else {
                std::cout << "Invalid input. Please enter 'h' for hit or 's' for stand." << std::endl;
            }
        }

        if (calculateSum(playerHand) > 21) {
            continue; 
        }

		std::cout << "Dealer's turn..\n";
        dealerTurn(dealerHand, deck);
        std::cout << "Dealer's hand: " << displayHand(dealerHand, true) << std::endl;
        int dealerSum = calculateSum(dealerHand);

        playerSum = calculateSum(playerHand);
        std::cout << "Final scores:\n";
        std::cout << "Player: " << playerSum << std::endl;
        std::cout << "Dealer: " << dealerSum << std::endl;

        if (playerSum > 21) {
            std::cout << "You busted! You lose your bet.\n";
        }
		else if (dealerSum > 21) {
			std::cout << "Dealer busted, you win! You gain your bet.\n";
			balance += bet * 2;
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
        if (balance < 1) {
            std::cout << "You have no money left. Game over!" << std::endl;
            break;
        }
    }
    return 0;
}