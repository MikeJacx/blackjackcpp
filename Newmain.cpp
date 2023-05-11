#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//card class, represents single card
class Card {
private:
	//suit index
	int suit;
	//rank 1..13
	int rank;
public:
	//constructor
	Card(int suit, int rank) :suit(suit), rank(rank) {}
	//display card
	friend ostream& operator<<(ostream& output, Card& card) {
		const string RANKS[] = { "0","Ace ","2","3","4","5","6","7","8","9","10","Jack","Queen","King" };
		const string SUITS[] = { "Clubs","Diamonds","Hearts","Spades" };
		output << RANKS[card.rank] << " of " << SUITS[card.suit];
		return output;
	}
	//getter for the value of the card
	int getValue()
	{
		if (rank <= 10) return rank;
		return 10;
	}

	//check if card is Ace
	bool isAce()
	{
		return rank == 1;
	}
};


//deck class, it contains 52 cards
class Deck {
private:
	//stores 52 cards
	vector<Card> deck;
public:
	//constructor
	Deck()
	{
		//create 52 cards
		//suits loop
		for (int i = 0; i < 4; i++)
		{
			//ranks loop
			for (int k = 1; k <= 13; k++)
			{
				deck.push_back(Card(i, k));
			}
		}
		//shuffle the deck
		random_shuffle(deck.begin(), deck.end());
	}

	//check if deck is empty
	bool isEmpty()
	{
		return deck.empty();
	}

	//deal card
	Card deal()
	{
		Card card = deck.back();
		deck.pop_back();
		return card;
	}


	//getter for deck size
	size_t getSize()
	{
		return deck.size();
	}
};

//hand class, player has one hand
class Hand {
private:
	//store the hand
	vector<Card> hand;

	//stored reference to deck
	Deck* deck;
	bool canHit;
public:
	//constructor takes the deck as reference
	Hand(Deck*& deck) :deck(deck), canHit(true) {}

	//hit
	bool hit()
	{
		if (!canHit) return false;

		if (!deck->isEmpty())
		{
			//deal card from the deck 
			Card card = deck->deal();

			//add card to hand
			hand.push_back(card);


			//if busted, it cannot hit anymore
			if (getValue() > 21) canHit = false;

			//return success
			return true;
		}
		//return failure
		return false;
	}

	//get value of the hand
	int getValue()
	{
		bool hasAce = false;
		int value = 0;

		//sum values of cards in the hand
		for (unsigned int i = 0; i < hand.size(); i++)
		{
			value += hand[i].getValue();
			if (hand[i].isAce()) hasAce = true;
		}

		//ace can be valued as 1 or 11
		if (hasAce && value <= 11) value += 10;

		return value;
	}


	//display hand
	friend ostream& operator<<(ostream& output, Hand& h)
	{
		for (unsigned int i = 0; i < h.hand.size(); i++)
		{
			output << h.hand[i] << endl;
		}
		output << "Hand value is " << h.getValue() << endl;

		return output;
	}


};



int main()
{
	//seed random with time
	srand((unsigned int)time(NULL));

	int playerWin = 0;
	int dealerWin = 0;

	//100 simulations
	for (int i = 0; i < 100; i++)
	{
		cout << endl << "======> Round " << i + 1 << endl;
		//create a deck
		Deck* deck = new Deck();

		//create a hand
		Hand hand(deck);

		//strategy is we hit as long as hand value is less than 17
		while (hand.getValue()<17)
		{
			hand.hit();
		}

		//display hand
		cout << hand << endl;

		//count and display winner
		if (hand.getValue() <= 21)
		{
			playerWin++;
			cout << "Player wins" << endl;
		}
		else
		{
			dealerWin++;
			cout << "Dealer wins" << endl;
		}

		//delete the deck
		delete deck;	
	}

	cout<< endl<<"===============================" << endl;
	cout << "Total Player Wins: " << playerWin << endl;
	cout << "Total Dealer Wins: " << dealerWin << endl;
}