/**
 * @class CardsSet
 * @brief Represents a deck or set of cards.
 *
 * The CardsSet class manages a collection of 52 cards and provides functions to initialize, shuffle,
 * draw, put back, and look at the cards in the set.
 */
class CardsSet
{
public:
    /**
     * @brief Constructs a new CardsSet object.
     * Initializes the number of cards to zero.
     */
    CardsSet() : number(0) {}

    /**
     * @brief Creates a new set of 52 cards.
     * Initializes the set with all cards of each suit and value, and sets the count to 52.
     */
    void novSet()
    {
        empty(); // empty the set of cards
        int index = 0;
        for (int suit = club; suit <= spade; ++suit)
        {
            for (int value = 1; value <= 13; ++value)
            {
                set[index++] = Card(static_cast<color>(suit), value);
            }
        }
        number = 52; // Ensure number is set to 52 after initializing all cards
    }

    /**
     * @brief Shuffles the set of cards
     *
     * Seeds the random number generator with the current time and randomly rearranges the cards in the set.
     */
    void shuffle()
    {
        // Seed the random number generator with the current time
        srand(static_cast<unsigned int>(time(0)));

        for (size_t i = 0; i < 52; ++i)
        {
            // Generate a random index between i and the end of the deck
            size_t randomIndex = i + rand() % (52 - i);
            // Swap the current card with the randomly chosen one
            swap(set[i], set[randomIndex]);
        }
    }

    /**
     * @brief Gets the number of cards currently in the set.
     * @return The number of cards in the set.
     */
    int numCards() { return number; }

    /**
     * @brief Draws a card from the set.
     * Decrements the card count and returns the drawn card.
     * @return The drawn card.
     * @throws std::runtime_error if there are no cards left to draw.
     */
    Card take()
    {
        if (number > 0)
        {
            return set[--number]; // Decrement number and return the card at the new position
        }
        throw std::runtime_error("No cards left to take.");
    }

    /**
     * @brief Puts a card back into the set.
     * Adds the specified card back to the set if there is room.
     * @param k The card to put back into the set.
     * @throws std::runtime_error if the set is full.
     */
    void put(Card k)
    {
        if (number < 52)
        {
            set[number++] = k; // Add the card to the current position and increment number
        }
        else
        {
            throw std::runtime_error("Cannot add more cards, deck is full.");
        }
    }

    /**
     * @brief Looks at a card in the set at the specified position.
     * @param no The position of the card to look at (1-based index).
     * @return The card at the specified position.
     * @throws std::out_of_range if the position is out of range.
     */
    Card lookIn(int no)
    {
        if (no > 0 && no <= number)
        {
            return set[no - 1];
        }
        throw std::out_of_range("Invalid card index.");
    }

    /**
     * @brief Empties the set of cards.
     * Resets the card count to zero.
     */
    void empty() { number = 0; }

private:
    Card set[52]; ///< Array to hold up to 52 cards in the set.
    int number;   ///< Number of cards currently in the set.
};