/**
 * @file main.cpp
 * @brief Entry point for the card game program.
 *
 * The main function simulates a card game between a player and a computer, where each tries to reach a score
 * as close as possible to 21 without exceeding it.
 */

#include <iostream>
using namespace std;

#include "myFile.h"
#include "Card.h"
#include "CardsSet.h"
#include "Player.h"

/**
 * @brief Main function to execute the card game.
 *
 * Initializes the deck of cards and creates player and computer objects. Runs a loop to allow
 * the player to play multiple rounds of the game, drawing cards and calculating scores to determine
 * the winner of each round.
 *
 * @return int Returns 0 upon successful execution.
 */
int main()
{
	CardsSet packet;		   ///< Deck of cards shared between the player and computer.
	Player you(packet, false); ///< Player object representing the human player.
	Player me(packet, true);   ///< Player object representing the computer.
	char answer[3];			   ///< Input buffer to read the player's response.
	bool continuous = true;	   ///< Flag to continue or end the game.
	cout << "Hello! " << endl;

	while (continuous)
	{
		cout << "A new game? " << endl;
		cin >> answer;
		continuous = answer[0] == 'y';
		if (continuous)
		{
			packet.novSet();  ///< Create a new set of 52 cards.
			packet.shuffle(); ///< Shuffle the deck of cards.
			packet.take();	  ///< Draw the first card from the shuffled deck (for initialization).

			int p1 = you.play(); ///< Player's turn to draw cards and calculate the score.

			if (p1 > 21)
			{
				cout << "You lost! " << endl;
			}
			else if (p1 == 21)
			{
				cout << "You won! " << endl;
			}
			else // The computer must play
			{
				int p2 = me.play(); ///< Computer's turn to draw cards and calculate the score.

				// Determine the winner based on the scores
				if (p2 <= 21 && p2 >= p1)
				{
					cout << "You lost! " << endl;
				}
				else
				{
					cout << "You won! " << endl;
				}
			}
		}
	}
	return 0;
}