#include "game.hpp"
#include "card.hpp"

#include <algorithm>

using namespace std;
namespace ariel
{
    static void shuffleDeck(vector<Card> &deck)
    {
        srand(time(nullptr));
        random_shuffle(deck.begin(), deck.end());
    }

    // ---------------------------------------------

    Game::Game(Player &first, Player &second)
        : p1(first), p2(second)
    {
        // Creating a random deck
        auto deck = createDeck();
        shuffleDeck(deck);

        // Splitting the cards to two players
        int size = deck.size();
        for (int i = 0; i < size; i++)
        {
            auto back = deck.back();
            deck.pop_back();

            if (i < size / 2)
                p1.push(back);
            else
                p2.push(back);
        }
    }

    // ---------------------------------------------

    void Game::internalPlayTurn(vector<Card> &total)
    {
        if (p1.stacksize() <= 0)
        {
            whoWins = p2.getName();
            return;
        }

        if (p2.stacksize() <= 0)
        {
            whoWins = p1.getName();
            return;
        }

        gamesCounter++;

        auto a = p1.getTop();
        auto b = p2.getTop();

        turns.back() += std::string(p1.getName() + " played " + a.getNumberString() + " of " + a.getTypeString() + " " +
                                    p2.getName() + " played " + b.getNumberString() + " of " + b.getTypeString() + ". ");

        if (a.getNumber() == b.getNumber())
        {
            turns.back() += " draw.";
            drawCounter++;

            total.insert(total.begin(), {p1.getTop(), p2.getTop(), a, b});

            if (p1.stacksize() == 0 || p2.stacksize() == 0)
            {
                int splitTotal = total.size() / 2;
                p1.addTaken(splitTotal);
                p2.addTaken(splitTotal);

                int middle = DeckSize / 2;
                if (p1.cardesTaken() == middle && p2.cardesTaken() == middle)
                {
                    whoWins = "Draw";
                    return;
                }
            }

            internalPlayTurn(total);
        }
        else
        {
            Player *winner = nullptr;

            if (a.getNumber() == 1 || b.getNumber() == 1)
            {
                if (a.getNumber() == 2)
                    winner = &p1;
                else if (b.getNumber() == 2)
                    winner = &p2;
                else
                    winner = a.getNumber() == 1 ? &p1 : &p2;
            }
            else
                winner = (a.getNumber() > b.getNumber()) ? &p1 : &p2;

            // winner->push(a);
            // winner->push(b);
            // for(auto c: total) winner->push(c);
            turns.back() += winner->getName() + " wins.";
        }
    }

    void Game::playTurn()
    {
        if(&p1 == &p2)
            throw runtime_error("Cannot start the game with the same player!");

        if(!whoWins.empty())
            throw "Game already played!";

        turns.push_back("");
        vector<Card> empty;
        internalPlayTurn(empty);
    }

    void Game::playAll()
    {
        while (whoWins.empty())
            playTurn();
    }

    // ---------------------------------------------

    void Game::printWiner()
    {
        cout << "The winner name: " << whoWins << endl;
    }

    void Game::printLastTurn()
    {
        if (turns.empty())
        {
            cout << "No turns were made." << endl;
            return;
        }

        cout << turns.back() << endl;
    }

    void Game::printLog()
    {
        for (auto str : turns)
            cout << str << endl;
    }

    void Game::printStats()
    {
        double drawRate = gamesCounter / drawCounter ;
        cout << "Amount of draw: " << drawCounter << ", Draw Rate: " << drawRate << endl;
    }

    // ---------------------------------------------

    vector<Card> Game::createDeck()
    {
        vector<Card> deck;
        for (int i = 0; i < DeckSize; i++)
            deck.push_back(Card((unsigned int)i));

        return deck;
    }
}
