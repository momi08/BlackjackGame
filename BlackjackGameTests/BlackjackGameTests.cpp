#include <map>
#include "CppUnitTest.h"
#include "../BlackjackGame/BlackjackGame.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlackjackGameTests
{
    TEST_CLASS(BlackjackGameTests)
    {
        TEST_METHOD(DeckInitializationTest) {
            std::vector<Card> deck = createDeck();
            Assert::AreEqual(52ull, deck.size());

            std::map<Rank, int> rankCount;
            for (const Card& card : deck) {
                rankCount[card.rank]++;
            }
            for (const auto& pair : rankCount) {
                Assert::AreEqual(4, pair.second);
            }

            std::map<Suit, int> suitCount;
            for (const Card& card : deck) {
                suitCount[card.suit]++;
            }
            for (const auto& pair : suitCount) {
                Assert::AreEqual(13, pair.second);
            }
        }

        TEST_METHOD(CardValueTest) {
            Card jack = { Rank::Jack, Suit::Hearts };
            Card queen = { Rank::Queen, Suit::Diamonds };
            Card king = { Rank::King, Suit::Clubs };
            Card ace = { Rank::Ace, Suit::Spades };

            Assert::AreEqual(10, cardValue(jack));
            Assert::AreEqual(10, cardValue(queen));
            Assert::AreEqual(10, cardValue(king));
            Assert::AreEqual(11, cardValue(ace));
        }

        TEST_METHOD(CalculateSumTest) {
            std::vector<Card> hand1 = { Card(Rank::Two, Suit::Hearts), Card(Rank::Three, Suit::Diamonds) };
            Assert::AreEqual(5, calculateSum(hand1));
            std::vector<Card> hand2 = { Card(Rank::Four, Suit::Clubs), Card(Rank::Five, Suit::Spades), Card(Rank::Six, Suit::Hearts) };
            Assert::AreEqual(15, calculateSum(hand2));
            std::vector<Card> hand3 = { Card(Rank::Seven, Suit::Diamonds), Card(Rank::Eight, Suit::Clubs), Card(Rank::Nine, Suit::Spades) };
            Assert::AreEqual(24, calculateSum(hand3));
        }

        TEST_METHOD(AceValueTest) {
            std::vector<Card> hand1 = { Card(Rank::Ace, Suit::Hearts), Card(Rank::Six, Suit::Spades) };
            Assert::AreEqual(17, calculateSum(hand1));

            std::vector<Card> hand2 = { Card(Rank::Ace, Suit::Hearts), Card(Rank::Ten, Suit::Diamonds), Card(Rank::Ten, Suit::Clubs) };
            Assert::AreEqual(21, calculateSum(hand2));

            std::vector<Card> hand3 = { Card(Rank::Ace, Suit::Hearts), Card(Rank::Four, Suit::Clubs), Card(Rank::Five, Suit::Spades) };
            Assert::AreEqual(20, calculateSum(hand3));

            std::vector<Card> hand4 = { Card(Rank::Ace, Suit::Hearts), Card(Rank::Ace, Suit::Clubs), Card(Rank::Ace, Suit::Diamonds), Card(Rank::Five, Suit::Spades) };
            Assert::AreEqual(18, calculateSum(hand4));
        }

        TEST_METHOD(BetValidationTest) {
            Assert::IsTrue(validateBet(1, 1));
            Assert::IsTrue(validateBet(5, 5));
            Assert::IsTrue(validateBet(20, 20));
            Assert::IsTrue(validateBet(100, 100));
            Assert::IsFalse(validateBet(3, 3));
            Assert::IsFalse(validateBet(25, 25));
            Assert::IsFalse(validateBet(40, 40));
            Assert::IsFalse(validateBet(101, 101));
        }

        TEST_METHOD(GetBet_ValidBet) {
            std::stringstream input("10\n");
            int bet = 0;
            int balance = 100;
            bool result = getBet(input, bet, balance);
            Assert::IsTrue(result);
            Assert::AreEqual(10, bet);
        }

        TEST_METHOD(GetBet_InvalidBet) {
            std::stringstream input("3\n");
            int bet = 0;
            int balance = 100;
            bool result = getBet(input, bet, balance);
            Assert::IsFalse(result);
        }

        TEST_METHOD(GetBet_NonNumericInput) {
            std::stringstream input("abc\n");
            int bet = 0;
            int balance = 100;
            bool result = getBet(input, bet, balance);
            Assert::IsFalse(result);
        }

        TEST_METHOD(DisplayHandTest) {
            std::vector<Card> hand = { Card(Rank::Ace, Suit::Spades), Card(Rank::Queen, Suit::Diamonds) };

            Assert::AreEqual(std::string("A♠ Q♦"), displayHand(hand, true));
            Assert::AreEqual(std::string("A♠"), displayHand(hand, false));
        }

        TEST_METHOD(PlayerTurnTest) {
            std::vector<Card> deck = {
                Card(Rank::Four, Suit::Clubs),
                Card(Rank::Nine, Suit::Hearts),
            };
            std::vector<Card> playerHand = { Card(Rank::Five, Suit::Spades), Card(Rank::Five, Suit::Clubs) };

            std::istringstream input("h\ns\n");
            bool result = playerTurn(playerHand, deck, input);

            Assert::IsTrue(calculateSum(playerHand) == 19);
        }

        TEST_METHOD(PlayerTurnTest_HitBlackJack) {
            std::vector<Card> deck = {
                Card(Rank::Ten, Suit::Hearts),
                Card(Rank::Queen, Suit::Diamonds)
            };

            std::vector<Card> playerHand = { Card(Rank::Five, Suit::Spades), Card(Rank::Six, Suit::Clubs) };

            std::istringstream input("h\n");

            bool result = playerTurn(playerHand, deck, input);

            Assert::IsTrue(calculateSum(playerHand) == 21);
            Assert::IsTrue(result);
        }

        TEST_METHOD(DealerTurnTest) {
            std::vector<Card> deck = {
                Card(Rank::Five, Suit::Hearts),
                Card(Rank::King, Suit::Clubs),
                Card(Rank::Six, Suit::Diamonds)
            };
            std::vector<Card> dealerHand = { Card(Rank::Six, Suit::Spades), Card(Rank::Five, Suit::Clubs) };
            bool result = dealerTurn(dealerHand, deck);
            Assert::IsTrue(calculateSum(dealerHand) >= 17);
            Assert::IsFalse(result);

            std::vector<Card> dealerHandBust = { Card(Rank::Ten, Suit::Spades), Card(Rank::Seven, Suit::Diamonds) };
            result = dealerTurn(dealerHandBust, deck);
            Assert::IsFalse(result);

			std::vector<Card> dealerHandBlackjack = { Card(Rank::Ace, Suit::Hearts), Card(Rank::King, Suit::Diamonds) };
			result = dealerTurn(dealerHandBlackjack, deck);
			Assert::IsFalse(result);
        }
    };
}
