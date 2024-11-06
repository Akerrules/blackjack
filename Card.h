#include <iostream>
using namespace std;
#include <cassert> //for assert()

enum color
{
    club,
    diamond,
    heart,
    spade
};

class Card
{
public:
    Card(color c = club, int v = 1);
    int value() { return val; }
    void write()
    {
        std::string colorName;
        switch (col)
        {
        case club:
            colorName = "Clubs";
            break;
        case diamond:
            colorName = "Diamonds";
            break;
        case heart:
            colorName = "Hearts";
            break;
        case spade:
            colorName = "Spades";
            break;
        default:
            colorName = "Unknown";
            break; // Safety check
        }

        // Convert the value (val) to a string for face cards and Ace
        std::string valueName;
        if (val == 1)
            valueName = "Ace";
        else if (val == 11)
            valueName = "Jack";
        else if (val == 12)
            valueName = "Queen";
        else if (val == 13)
            valueName = "King";
        else
            valueName = std::to_string(val);

        // Print the card's value and suit in the required format
        std::cout << valueName << " of " << colorName << std::endl;
    };

private:
    color col;
    int val;
};

/*Constructor*/
Card::Card(color c, int v)
{
    assert(v >= 1 && v <= 13); // we use a standard function void assert (int expression)
    // which indicates an error message if the expression is false.
    col = c;
    val = v;
}
