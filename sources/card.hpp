#pragma once

// #include "game.hpp"
#include <iostream>
#include <vector>

#include <stdexcept>
using namespace std;

namespace ariel
{
    class Card
    {
    public:
        Card(unsigned int card = 0);

        unsigned int getNumber();

        enum class Type
        {
            Diamonds = 1,
            Clubs,
            Hearts,
            Spades,
            Unknown
        };
        Type getType();

        string getTypeString();
        string getNumberString();

    private:
        static const unsigned int MaxCards = 52;
        unsigned int number;
    };
}
