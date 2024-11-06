/**
 * @class Player
 * @brief Represents a player in the card game.
 *
 * The Player class manages the hand of cards for a player (human or computer),
 * and provides functions to draw cards, calculate points, and determine if the player wants an additional card.
 */
class Player
{
public:
    /**
     * @brief Constructs a new Player object.
     * @param cardPacket Reference to the shared deck of cards.
     * @param isComputer True if the player is a computer, false otherwise.
     */
    Player(CardsSet &cardPacket, bool isComputer) : packet(cardPacket), computer(isComputer) {}

    /**
     * @brief Allows the player to play their turn by drawing cards and calculating their score.
     * @return The total score of the player at the end of their turn.
     */
    int play();

private:
    CardsSet inHand;     ///< Cards held by the player in their hand.
    CardsSet &packet;    ///< Reference to the shared deck of cards.
    const bool computer; ///< Indicates if the player is a computer.

    /**
     * @brief Calculates the total points of the cards in the player's hand.
     * @return The total points of the player's hand.
     */
    int countPoints();

    /**
     * @brief Determines if the player wants an additional card.
     * @return True if the player wants an additional card, false otherwise.
     */
    bool wantsAdditionalCard() const;
};

int Player::play()
{
    std::string playername = computer ? "computer" : "you";
    inHand.empty();
    // debug
    cout << countPoints() << endl;

    while (true)
    {
        // Draw a card from the shared deck
        Card drawnCard = packet.take();
        inHand.put(drawnCard);

        // Display the drawn card
        std::cout << "\n"
                  << playername << " get Card: ";
        drawnCard.write();

        // Calculate and display the current score
        int currentScore = countPoints();
        std::cout << "\n"
                  << playername << " score is " << currentScore << " points\n";

        // If the score exceeds 21, return immediately as the player loses
        if (currentScore > 21)
        {
            return currentScore;
        }

        // Decide whether to draw another card based on whether the player is a computer
        if (!computer)
        {
            if (!wantsAdditionalCard())
            {
                break;
            }
        }
        else
        {
            // Computer strategy: stop if score is 17 or higher
            if (currentScore >= 17)
            {
                break;
            }
        }
    }

    return countPoints();
}

int Player::countPoints()
{
    int total = 0;
    int aceCount = 0;

    // Calculate the total value of the cards in hand
    for (int i = 1; i <= inHand.numCards(); ++i)
    {
        int cardValue = inHand.lookIn(i).value();
        if (cardValue == 1)
        { // Ace handling
            aceCount++;
            total += 14; // Treat Ace as 14 initially
        }
        else if (cardValue > 10)
        {
            total += 10; // Face cards (Jack, Queen, King) count as 10
        }
        else
        {
            total += cardValue;
        }
    }

    // Adjust Ace value if total exceeds 21
    while (total > 21 && aceCount > 0)
    {
        total -= 13; // Convert an Ace from 14 to 1
        aceCount--;
    }

    return total;
}

bool Player::wantsAdditionalCard() const
{
    char choice;
    std::cout << "Any additional card? (y/n): ";
    std::cin >> choice;
    return choice == 'y' || choice == 'Y';
}