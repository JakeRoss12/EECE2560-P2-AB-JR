#ifndef DECK_H
#define DECK_H

#include <vector>

#include "Card.h"
#include "Node.h"


// Deck Class with Linked List
class Deck {
public:
    // Constructor: Initializes an empty deck and fills it with cards
    Deck();

    // Destructor
    ~Deck();

    // Deal: Returns the top card and removes it from deck
    Card deal();

    // Replace: Places a card at the bottom of the deck
    void replace(const Card& A);

    // Output operator for deck objects
    friend ostream &operator<<(ostream &out, const Deck &A);

    //Shuffles the cards
    void shuffle();

private:
    Node* first_card;

public:
    // Gets the first card in deck
    const Node* getFirstCard() const { return first_card; }
};


#endif
