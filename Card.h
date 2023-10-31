#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

using namespace std;

// Card Class
class Card {
public:

    // Constructors
    Card(int v, int s);
    Card(const Card& A);

    // Sets value of card
    void setValue(int v);

    // Sets suit of card
    void setSuit(int s);

    // Get value of card
    int getValue() const;

    // Get suit of card
    int getSuit() const;

    // Output
    friend ostream &operator<<(ostream&out, const Card&A);

    // Assignment
    Card& operator=(const Card& A);

private:
    int value;
    int suit; // 1=club, 2=diamond, 3=heart, 4=spade
};


#endif
