#include "BlackjackGame.h"

int main() {
    int balance = 0;
    int bet = 0;

    std::cout << "Starting a game of Blackjack!" << std::endl;
    if (!getValidBalance(balance)) {
        return 0;
    }
    std::cout << "Your starting balance: " << balance << std::endl;
    while (balance >= 1) {
        if (!getValidBet(bet, balance)) {
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

        std::cout << "Your hand: ";
        displayHand(playerHand);
        std::cout << "Dealer's visible card: " << dealerHand[0].cardName << std::endl;

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

        playerTurn(playerHand, deck);

        if (calculateSum(playerHand) > 21) {
            std::cout << "You busted! You lose your bet.\n";
            std::cout << "Your new balance: " << balance << std::endl;
            continue;
        }

        dealerTurn(dealerHand, deck);

        playerSum = calculateSum(playerHand);
        int dealerSum = calculateSum(dealerHand);

        std::cout << "Final scores:\n";
        std::cout << "Player: " << playerSum << std::endl;
        std::cout << "Dealer: " << dealerSum << std::endl;
        if (playerSum > 21) {
            std::cout << "You busted! You lose your bet.\n";
        }
        else if (dealerSum > 21 || playerSum > dealerSum) {
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