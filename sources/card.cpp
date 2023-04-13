#include "card.hpp"

#include <exception>

namespace ariel
{
    Card::Card(unsigned int card)
        : number((int)card + 1)
    {
        if (number - 1>= MaxCards)
            throw runtime_error("Unknown card!");
    }

    // ---------------------------------------------

    int Card::getNumber() { 
        return ((number - 1) % 13) + 1; 
    }

    Card::Type Card::getType()
    {
        if (number - 1 >= MaxCards)
            return Type::Unknown;

        if (number < 13)
            return Type::Diamonds;
        if (number < 26)
            return Type::Clubs;
        if (number < 39)
            return Type::Hearts;
        return Type::Spades;
    }

    string Card::getTypeString()
    {
        const auto Type = getType();

        switch (Type)
        {
        case Type::Clubs:
            return "Clubs";
        case Type::Diamonds:
            return "Diamonds";
        case Type::Hearts:
            return "Hearts";
        case Type::Spades:
            return "Spades";
        default:
            return "Unknown";
        }
    }

    string Card::getNumberString()
    {
        auto num = getNumber();
        switch (num)
        {
        case 13:
            return "King";
        case 12:
            return "Queen";
        case 11:
            return "Prince";
        default:
            return to_string(num);
        }
    }
}
