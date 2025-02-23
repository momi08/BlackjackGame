#include "pch.h"
#include "CppUnitTest.h"
#include "BlackjackGame.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlackjackGameTests
{
    TEST_CLASS(BlackjackGameTests)
    {
    public:
        TEST_METHOD(DeckInitializationTest)
        {
            vector<Card> deck = createDeck();
            Assert::AreEqual(52, (int)deck.size(), L"Deck needs to have 52 cards!");
            map<string, int> cardCount;
            for (const Card& card : deck) {
                cardCount[card.name]++;
            }

            for (auto& pair : cardCount) {
                Assert::AreEqual(4, pair.second, L"Each card must appear four times in a deck!");
            }
        }

        TEST_METHOD(DeckDealingTest)
        {
            vector<Card> deck = createDeck();
            vector<Card> playerHand;
            vector<Card> dealerHand;

            playerHand.push_back(deck.back()); deck.pop_back();
            dealerHand.push_back(deck.back()); deck.pop_back();
            playerHand.push_back(deck.back()); deck.pop_back();
            dealerHand.push_back(deck.back()); deck.pop_back();

            Assert::AreEqual(48, (int)deck.size(), L"After dealing, deck has to have 48 cards remaining!");
        }

        TEST_METHOD(CardCountAfterDealingTest)
        {
            vector<Card> deck = createDeck();
            vector<Card> playerHand;

            int kingsDrawn = 0;
            for (int i = 0; i < deck.size(); i++) {
                if (deck[i].name == "K" && kingsDrawn < 2) {
                    playerHand.push_back(deck[i]);
                    deck.erase(deck.begin() + i);
                    kingsDrawn++;
                    i--;
                }
            }
            int kingCount = 0;
            for (const Card& card : deck) {
                if (card.name == "K") {
                    kingCount++;
                }
            }
            Assert::AreEqual(2, kingCount, L"After dealing two K's, two more must remain in the deck!");
        }

        TEST_METHOD(AceValueTest)
        {
            vector<Card> hand1 = { {"A", 1}, {"6", 6} };
            Assert::AreEqual(17, calculateSum(hand1), L"Ace should be valued 11!");

            vector<Card> hand2 = { {"A", 1}, {"10", 10}, {"10", 10} }; 
            Assert::AreEqual(21, calculateSum(hand2), L"Ace should be valued 1!");

            vector<Card> hand3 = { {"A", 1}, {"A", 1}, {"9", 9} }; 
            Assert::AreEqual(21, calculateSum(hand3), L"Ace is not calculated correctly!");
        }

        TEST_METHOD(PlayerBustsTest)
        {
            vector<Card> hand = { {"10", 10}, {"10", 10}, {"5", 5} };
            Assert::IsTrue(calculateSum(hand) > 21, L"Player busts! (over 21)");
        }

        TEST_METHOD(PlayerBlackjackTest)
        {
            vector<Card> hand = { {"10", 10}, {"A", 11} };
            Assert::IsTrue(calculateSum(hand) = 21, L"Player gets Blacjack!");
        }

        TEST_METHOD(DealerStandsOn17Test)
        {
            vector<Card> dealerHand = { {"10", 10}, {"7", 7} };
            Assert::AreEqual(17, calculateSum(dealerHand), L"Dealer is stopping at 17!");
        }

        TEST_METHOD(DealerStandsOnMoreThan17Test)
        {
            vector<Card> dealerHand = { {"10", 10}, {"2", 2}, {"6", 6} };
            Assert::AreEqual(18, calculateSum(dealerHand), L"Dealer is stopping at 18!");
        }

        TEST_METHOD(DealerBustsTest)
        {
            vector<Card> dealerHand = { {"10", 10}, {"2", 2}, {"K", 10} };
            Assert::AreEqual(22, calculateSum(dealerHand), L"Dealer busts! (over 21)");
        }

        TEST_METHOD(InitialBalanceTest)
        {
            int balance = 50;
            Assert::IsTrue(balance >= 1 && balance <= 100, L"Balance needs to be between 1 and 100!");
        }

        TEST_METHOD(BetAcceptedValuesTest)
        {
            Assert::IsTrue(isValidBet(2), L"Bet of 2 is valid!");
            Assert::IsTrue(isValidBet(5), L"Bet of 5 is valid!");
            Assert::IsTrue(isValidBet(10), L"Bet of 10 is valid!");
            Assert::IsTrue(isValidBet(50), L"Bet of 50 is valid!");
            Assert::IsTrue(isValidBet(100), L"Bet of 100 is valid!");
            Assert::IsFalse(isValidBet(3), L"Bet of 3 is invalid!");
            Assert::IsFalse(isValidBet(7), L"Bet of 7 is invalid!");
            Assert::IsFalse(isValidBet(15), L"Bet of 15 is invalid!");
            Assert::IsFalse(isValidBet(30), L"Bet of 30 is invalid!");
            Assert::IsFalse(isValidBet(200), L"Bet of 200 is invalid!");
        }

        TEST_METHOD(BetCannotExceedBalanceTest)
        {
            int balance = 10;
            int bet = 15;
            Assert::IsTrue(bet <= balance, L"Bet should be lower than the balance!");
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
