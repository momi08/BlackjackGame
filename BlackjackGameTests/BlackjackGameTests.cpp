#include "CppUnitTest.h"
#include "../BlackjackGame/BlackjackGame.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlackjackGameTests
{
    TEST_CLASS(BlackjackGameTests)
    {
        TEST_METHOD(DeckInitializationTest)
        {
            std::vector<Card> deck = createDeck();
            Assert::AreEqual(52ull, deck.size(), L"Deck needs to have 52 cards!");

            std::map<Rank, int> rankCount;
            for (const Card& card : deck) {
                rankCount[card.rank]++;
            }
            for (const auto& pair : rankCount) {
                Assert::AreEqual(4, pair.second, L"Each rank must appear 4 times in a deck!");
            }

            std::map<Suit, int> suitCount;
            for (const Card& card : deck) {
                suitCount[card.suit]++;
            }
            for (const auto& pair : suitCount) {
                Assert::AreEqual(13, pair.second, L"Each suit must appear 13 times in a deck!");
            }
        }

        TEST_METHOD(CardValueTest)
        {
            Card jack = { Rank::Jack, Suit::Hearts };
            Card queen = { Rank::Queen, Suit::Diamonds };
            Card king = { Rank::King, Suit::Clubs };
            Card ace = { Rank::Ace, Suit::Spades };

            Assert::AreEqual(10, cardValue(jack), L"Jack should be valued 10!");
            Assert::AreEqual(10, cardValue(queen), L"Queen should be valued 10!");
            Assert::AreEqual(10, cardValue(king), L"King should be valued 10!");
            Assert::AreEqual(11, cardValue(ace), L"Ace should be valued 11!");
        }

        TEST_METHOD(CalculateSumTest)
        {
            std::vector<Card> hand1 = { Card(Rank::Two, Suit::Hearts), Card(Rank::Three, Suit::Diamonds) };
            Assert::AreEqual(5, calculateSum(hand1), L"Sum should be 5!");
            std::vector<Card> hand2 = { Card(Rank::Four, Suit::Clubs), Card(Rank::Five, Suit::Spades), Card(Rank::Six, Suit::Hearts) };
            Assert::AreEqual(15, calculateSum(hand2), L"Sum should be 15!");
            std::vector<Card> hand3 = { Card(Rank::Seven, Suit::Diamonds), Card(Rank::Eight, Suit::Clubs), Card(Rank::Nine, Suit::Spades) };
            Assert::AreEqual(24, calculateSum(hand3), L"Sum should be 24!");
        }

        TEST_METHOD(AceValueTest)
        {
            std::vector<Card> hand1 = { Card(Rank::Ace, Suit::Hearts), Card(Rank::Six, Suit::Spades) };
            Assert::AreEqual(17, calculateSum(hand1), L"Ace should be valued 11!");

            std::vector<Card> hand2 = { Card(Rank::Ace, Suit::Hearts), Card(Rank::Ten, Suit::Diamonds), Card(Rank::Ten, Suit::Clubs) };
            Assert::AreEqual(21, calculateSum(hand2), L"Ace should be valued 1 to prevent a bust!");

            std::vector<Card> hand3 = { Card(Rank::Ace, Suit::Hearts), Card(Rank::Four, Suit::Clubs), Card(Rank::Five, Suit::Spades) };
            Assert::AreEqual(20, calculateSum(hand3), L"Ace should be valued 11 if the total is less than or equal to 21!");
        }

        TEST_METHOD(BetValidationTest)
        {
            Assert::IsTrue(validateBet(1, 1), L"Bet must be valid!");
            Assert::IsTrue(validateBet(5, 5), L"Bet must be valid!");
            Assert::IsTrue(validateBet(20, 20), L"Bet must be valid!");
            Assert::IsTrue(validateBet(100, 100), L"Bet must be valid!");
            Assert::IsFalse(validateBet(3, 3), L"Bet must be a valid amount!");
            Assert::IsFalse(validateBet(25, 25), L"Bet must be a valid amount!");
            Assert::IsFalse(validateBet(40, 40), L"Bet must be a valid amount!");
            Assert::IsFalse(validateBet(101, 101), L"Bet must be a va?od amount!");
        }

        TEST_METHOD(GetBet_ValidBet)
        {
            std::stringstream input("10\n");
            int bet = 0;
            int balance = 100;
            bool result = getBet(input, bet, balance);
            Assert::IsTrue(result, L"Valid bet should return true.");
            Assert::AreEqual(10, bet, L"Bet should be set to 10.");
        }

        TEST_METHOD(GetBet_InvalidBet)
        {
            std::stringstream input("3\n");
            int bet = 0;
            int balance = 100;
            bool result = getBet(input, bet, balance);
            Assert::IsFalse(result, L"Invalid bet should return false.");
        }

        TEST_METHOD(GetBet_NonNumericInput)
        {
            std::stringstream input("abc\n");
            int bet = 0;
            int balance = 100;
            bool result = getBet(input, bet, balance);
            Assert::IsFalse(result, L"Non-numeric input should return false.");
        }

        TEST_METHOD(PlayerTurnTest) {
            std::vector<Card> deck = {
                Card(Rank::Four, Suit::Clubs),
                Card(Rank::Nine, Suit::Hearts),
            };
            std::vector<Card> playerHand = { Card(Rank::Five, Suit::Spades), Card(Rank::Five, Suit::Clubs) };
            std::istringstream input("h\ns\n");
            std::cin.rdbuf(input.rdbuf());

            displayHand(playerHand, true);
            bool result = playerTurn(playerHand, deck);
            displayHand(playerHand, true);

            Assert::IsTrue(calculateSum(playerHand) == 19, L"Player should have 19 after hitting and standing!");

            std::cin.rdbuf(std::cin.rdbuf());
        }

        TEST_METHOD(PlayerTurnTest_HitBlackJack) {
            std::vector<Card> deck = {
                Card(Rank::Ten, Suit::Hearts),
                Card(Rank::Queen, Suit::Diamonds)
            };

            std::vector<Card> playerHand = { Card(Rank::Five, Suit::Spades), Card(Rank::Six, Suit::Clubs) };
            std::istringstream input("h\n");
            std::cin.rdbuf(input.rdbuf());

            displayHand(playerHand, true);
            bool result = playerTurn(playerHand, deck); 
            displayHand(playerHand, true);

            Assert::IsTrue(calculateSum(playerHand) == 21, L"Player should have 21 after hitting");
            std::cin.rdbuf(std::cin.rdbuf());
        }

        TEST_METHOD(DealerTurnTest) {
            std::vector<Card> deck = {
                Card(Rank::Five, Suit::Hearts),
                Card(Rank::King, Suit::Clubs),
                Card(Rank::Six, Suit::Diamonds)
            };
            std::vector<Card> dealerHand = { Card(Rank::Six, Suit::Spades), Card(Rank::Five, Suit::Clubs) };
            bool result = dealerTurn(dealerHand, deck);
            Assert::IsTrue(calculateSum(dealerHand) >= 17, L"Dealer must stop at 17 or more!");
            Assert::IsFalse(result, L"Dealer should not bust!");

            std::vector<Card> dealerHandBust = { Card(Rank::Ten, Suit::Spades), Card(Rank::Seven, Suit::Diamonds) };
            result = dealerTurn(dealerHandBust, deck);
            Assert::IsFalse(result, L"Dealer should not bust when already at 17!");

			std::vector<Card> dealerHandBlackjack = { Card(Rank::Ace, Suit::Hearts), Card(Rank::King, Suit::Diamonds) };
			result = dealerTurn(dealerHandBlackjack, deck);
			Assert::IsFalse(result, L"Dealer should not draw when already at 21!");
        }
    };
}
