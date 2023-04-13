#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>
//#include <stdlib.h>
#include <iomanip>
#include "player.hpp"

using namespace std;

namespace ariel
{
    class Game
    {
    public:
        Game(Player &first, Player &second);

        void playTurn();
        void playAll();

        void printLastTurn();
        void printWiner();
        void printLog();
        void printStats();

    private:
        // Functions
        vector<Card> createDeck();
        void internalPlayTurn(vector<Card> &total);

        // Variables
        Player &p1;
        Player &p2;
        string whoWins;
        vector<string> turns;

        int gamesCounter = 0;
        int drawCounter = 0;
        unsigned int win_p1 = 0;
        unsigned int win_p2 = 0;

        // Constants
        static const int DeckSize = 52;
    };
}
