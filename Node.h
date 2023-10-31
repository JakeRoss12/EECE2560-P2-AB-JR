#ifndef NODE_H
#define NODE_H

#include "Card.h"

// LinkedList Node
class Node {

public:
    Card card;
    Node* next;

    // Constructor: Initializes a node and clears next pointer
    Node(Card c) : card(c), next(nullptr) {}
};

#endif
