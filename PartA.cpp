#include <iostream>
//#include <vector>
//#include <ctime>
//#include <algorithm>

using namespace std;

// Card Class
class Card {
    public:
    
    // Constructor
    Card(int v, int s);

    // Sets value of card
    void setValue(int v);

    // Sets suit of card
    void setSuit(int s);

    // Get value of card
    int getValue();

    // Get suit of card
    int getSuit();

    // Print card's value and suit
    friend ostream & operator<<(ostream&out, Card&A);

    private:
    int value;
    int suit; // 1=club, 2=diamond, 3=heart, 4=spade
};

// Card Class: Constructor
Card::Card(int v, int s) {
    value = v;
    suit = s;
};

// Card Class: setValue
void Card::setValue(int v) {
    value = v;
};

// Card Class: setSuit
void Card::setSuit(int s) {
    suit = s;
};

// Card Class: getValue
int Card::getValue() {
    return value;
};

// Card Class: getSuit
int Card::getSuit() {
    return suit;
};