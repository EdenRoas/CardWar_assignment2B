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

        // p1.print();
        // p2.print();
        
    }

    // ---------------------------------------------

    void Game::internalPlayTurn(vector<Card> &total)
    {
        gamesCounter++;
        
        if(p1.stacksize() <= 0 || p2.stacksize() <= 0) {
            whoWins = p1.cardesTaken() > p2.cardesTaken() ? p1.getName() : p2.getName();
            return;
        }

        Card a, b;
        a = p1.getTop();
        b = p2.getTop();

        //cout << "AAA: " << p1 << endl;

        turns.back() += string(p1.getName() + " played " + a.getNumberString() + " of " + a.getTypeString() + " " +
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

            if(total.empty())
                winner->addTaken(2);
            else
                winner->addTaken(2 + total.size());

            // winner->push(a);
            // winner->push(b);
            // 
            turns.back() += winner->getName() + " wins.";
            if (winner->getName() == p1.getName())
                win_p1++;
            else
                win_p2++;
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

        turns.erase(turns.begin());
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
         //Player1
        
        cout << "******* Player 1 Stats: *******" << endl;
        cout << "Amount of Turns:" << double(turns.size()) << ", Amoount of win for player1: " << win_p1 << endl;
        //double p1WinRate = (static_cast<double>(double)win_p1 / turns.size()) ;
        double p1WinRate = static_cast<double>((double)win_p1 / turns.size())*100;
        //string str_p1WinRate = to_string(p1WinRate);
        cout <<  "Win Rate for Player 1: " << setprecision(2) << p1WinRate << " %"<< endl; 
        cout << "Amoount of CardesTaken: " << p1.cardesTaken() << endl;
        //Player2
        cout << "******* Player 2 Stats: *******" << endl;
        cout << "Amount of Turns:" << turns.size() << ", Amoount of win for player2: " << win_p2 << endl;
        double p2WinRate = static_cast<double>((double)win_p2 / turns.size())*100;
        //string str_p2WinRate = to_string(p2WinRate);
        cout <<  "Win Rate for Player 2: " << setprecision(2) << p2WinRate << " %"<< endl; 
        cout << "Amoount of CardesTaken: " << p2.cardesTaken() << endl;
        //DrawRate
        cout << "******* Draw Stats: *******" << endl;
        double drawRate = static_cast<double>((double)drawCounter / gamesCounter) * 100;
        cout << "Amount of draw: " << drawCounter << ", Draw Rate: " << setprecision(2) << drawRate << endl;

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
