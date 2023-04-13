#pragma once

// #include "game.hpp"
#include <iostream>
#include <vector>

#include <stdexcept>

#include "card.hpp"

using namespace std;

namespace ariel
{
    class Player
    {
    public:
        Player(string name);

        int stacksize();
        int cardesTaken();

        void addTaken(int adder);

        void push(Card card);
        Card getTop();

        const string &getName();

        void print();

    private:
        string m_name;
        vector<Card> deck;
        int taken = 0;
    };
}
