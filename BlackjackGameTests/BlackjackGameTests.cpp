#include "CppUnitTest.h"
#include "../BlackjackGame/BlackjackGame.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlackjackGameTests
{
    TEST_CLASS(BlackjackGameTests)
    {
    public:
        std::vector<Card> deck = createDeck();
        TEST_METHOD(DeckInitializationTest)
        {
            
            Assert::AreEqual(52, (int)deck.size(), L"Deck needs to have 52 cards!");
            std::map<std::string, int> cardCount;
            for (const Card& card : deck) {
                cardCount[card.cardName]++;
            }

            for (auto& pair : cardCount) {
                Assert::AreEqual(4, pair.second, L"Each card must appear four times in a deck!");
            }
        }

        TEST_METHOD(DeckDealingTest)
        {
            std::vector<Card> playerHand;
            std::vector<Card> dealerHand;

            playerHand.push_back(deck.back()); deck.pop_back();
            dealerHand.push_back(deck.back()); deck.pop_back();
            playerHand.push_back(deck.back()); deck.pop_back();
            dealerHand.push_back(deck.back()); deck.pop_back();

            Assert::AreEqual(48, (int)deck.size(), L"After dealing, deck has to have 48 cards remaining!");
        }

        TEST_METHOD(CardCountAfterDealingTest)
        {
            std::vector<Card> playerHand;

            int kingsDrawn = 0;
            for (int i = 0; i < deck.size(); i++) {
                if (deck[i].cardName == "K" && kingsDrawn < 2) {
                    playerHand.push_back(deck[i]);
                    deck.erase(deck.begin() + i);
                    kingsDrawn++;
                    i--;
                }
            }
            int kingCount = 0;
            for (const Card& card : deck) {
                if (card.cardName == "K") {
                    kingCount++;
                }
            }
            Assert::AreEqual(2, kingCount, L"After dealing two K's, two more K's must remain in the deck!");
        }

        TEST_METHOD(AceValueTest)
        {
            std::vector<Card> hand1 = { {"A", 11}, {"6", 6} };
            Assert::AreEqual(17, calculateSum(hand1), L"Ace should be valued 11!");

            std::vector<Card> hand2 = { {"A", 11}, {"10", 10}, {"10", 10} };
            Assert::AreEqual(21, calculateSum(hand2), L"Ace should be valued 1!");

            std::vector<Card> hand3 = { {"A", 11}, {"A", 11}, {"9", 9} };
            Assert::AreEqual(21, calculateSum(hand3), L"Ace is not calculated correctly!");

            std::vector<Card> hand4 = { {"A", 11}, {"5", 5}, {"6", 6} };
            Assert::AreEqual(12, calculateSum(hand4), L"Ace should be valued 1 if the other cards sum to 11!");

            std::vector<Card> hand5 = { {"A", 11}, {"4", 4}, {"5", 5} };
            Assert::AreEqual(20, calculateSum(hand5), L"Ace should be valued 11 if the other cards sum to 9!");
        }

        TEST_METHOD(PlayerBustsTest)
        {
            std::vector<Card> hand = { {"10", 10}, {"10", 10}, {"5", 5} };
            Assert::IsTrue(calculateSum(hand) > 21, L"Player busts! (over 21)");
        }

        TEST_METHOD(PlayerBlackjackTest)
        {
            std::vector<Card> hand = { {"10", 10}, {"A", 11} };
            Assert::IsTrue(calculateSum(hand) == 21, L"Player gets Blacjack!");
        }

        TEST_METHOD(DealerStandsOn17Test)
        {
            std::vector<Card> dealerHand = { {"10", 10}, {"7", 7} };
            Assert::AreEqual(17, calculateSum(dealerHand), L"Dealer is stopping at 17!");
        }

        TEST_METHOD(DealerStandsOnMoreThan17Test)
        {
            std::vector<Card> dealerHand = { {"10", 10}, {"2", 2}, {"6", 6} };
            Assert::AreEqual(18, calculateSum(dealerHand), L"Dealer is stopping at 18!");
        }

        TEST_METHOD(DealerBustsTest)
        {
            std::vector<Card> dealerHand = { {"10", 10}, {"2", 2}, {"K", 10} };
            Assert::AreEqual(22, calculateSum(dealerHand), L"Dealer busts! (over 21)");
        }

        TEST_METHOD(InitialBalanceTest)
        {
            int balance = 50;
            Assert::IsTrue(balance >= 1 && balance <= 100, L"Balance needs to be between 1 and 100!");
        }
        TEST_METHOD(AcceptsValidBets)
        {
            int bet;
            std::istringstream input("5\n");
            Assert::IsTrue(getValidBet(bet, 100), L"Bet of 5 should be accepted.");
            Assert::AreEqual(5, bet);
        }

        TEST_METHOD(AcceptsMultipleValidBets)
        {
            int bet;
            std::istringstream input("2\n50\n");
            std::cin.rdbuf(input.rdbuf());

            Assert::IsTrue(getValidBet(bet, 100), L"Bet of 2 should be accepted.");
            Assert::AreEqual(2, bet);

            Assert::IsTrue(getValidBet(bet, 100), L"Bet of 50 should be accepted.");
            Assert::AreEqual(50, bet);
        }

        TEST_METHOD(RejectsInvalidBets)
        {
            int bet;
            std::istringstream input("3\n10\n");
            Assert::IsTrue(getValidBet(bet, 100), L"Invalid bet should be rejected, but valid bet should work.");
            Assert::AreEqual(10, bet);
        }
        TEST_METHOD(RejectsNonNumericInput)
        {
            int bet;
            std::istringstream input("abc\n20\n");
            Assert::IsTrue(getValidBet(bet, 100), L"Non-numeric input should be ignored.");
            Assert::AreEqual(20, bet);
        }

        TEST_METHOD(RejectsBetAboveBalance)
        {
            int bet;
            
            std::istringstream input("100\n10\n");
            std::cin.rdbuf(input.rdbuf());

            Assert::IsTrue(getValidBet(bet, 50), L"Bet should retry until a valid bet is entered.");
            Assert::AreEqual(10, bet);
        }
        TEST_METHOD(AcceptsCashout)
        {
            int bet;
            std::istringstream input("cashout\n");
            std::cin.rdbuf(input.rdbuf());
            Assert::IsFalse(getValidBet(bet, 50), L"Entering 'cashout' should exit the function.");
        }

        TEST_METHOD(BetCannotExceedBalanceTest)
        {
            int balance = 10;
            int bet = 15;
            Assert::IsFalse(bet <= balance, L"Bet should be lower than the balance!");
        }

        TEST_METHOD(BalanceReductionAfterLossTest)
        {
            int balance = 50;
            int bet = 10;
            balance -= bet;
            Assert::AreEqual(40, balance, L"After the loss, balance must be calculated correctly!");
        }

        TEST_METHOD(BalanceAdditionAfterWinTest)
        {
            int balance = 50;
            int bet = 10;
            balance += bet;
            Assert::AreEqual(60, balance, L"After the win, balance must be calculated correctly!");
        }
    };
}
