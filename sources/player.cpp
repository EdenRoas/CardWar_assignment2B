#include "player.hpp"

using namespace std;
namespace ariel
{
    Player::Player(string name)
        : m_name(name), deck()
    {
    }

    // ---------------------------------------------

    int Player::stacksize() { 
        if(deck.empty())
            return 0;
        
        return deck.size(); 
    }
    int Player::cardesTaken() { return taken; }

    // ---------------------------------------------

    const string &Player::getName()
    {
        return m_name;
    }

    // ---------------------------------------------

    void Player::push(Card card)
    {
        deck.insert(deck.begin(), card);
    }

    Card Player::getTop()
    {
        Card top = deck.back();
        deck.pop_back();
        //top = top.getNumber();
        return top;
    }

    // ---------------------------------------------

    void Player::addTaken(int adder)
    {
        taken += adder;
    }

    // ---------------------------------------------
    
    void Player::print()
    {
        cout << "Player name: " << m_name << "\nDeck: {";
        for (auto c : deck)
            cout << c.getNumber() << ",";
        cout << "}" << endl;
    }

}
