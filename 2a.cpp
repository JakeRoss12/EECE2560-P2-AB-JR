#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <ctime>
#include <algorithm>

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
    int getValue() const;

    // Get suit of card
    int getSuit() const;

    // Output
    friend ostream &operator<<(ostream&out, const Card&A);

private:
    int value;
    int suit; // 1=club, 2=diamond, 3=heart, 4=spade
};

// Card Class: Constructor
Card::Card(int v, int s) {
    value = v;
    suit = s;
}

// Card Class: setValue
void Card::setValue(int v) {
    value = v;
}

// Card Class: setSuit
void Card::setSuit(int s) {
    suit = s;
}

// Card Class: getValue
int Card::getValue() const {
    return value;
}

// Card Class: getSuit
int Card::getSuit() const {
    return suit;
}

// Card Class: output
ostream &operator<<(ostream&out, const Card&A) {
    string suit_string;
    if (A.getSuit() == 1) {
        suit_string = "club";
    } else if (A.getSuit() == 2) {
        suit_string = "diamond";
    } else if (A.getSuit() == 3) {
        suit_string = "heart";
    } else if (A.getSuit() == 4) {
        suit_string = "spade";
    }

    string value_string; // Name certain cards
    if (A.getValue() == 1) {
        value_string = "Ace";  // Ace = Value 1
    } else if (A.getValue() == 11) {
        value_string = "Jack"; // Jack = Value 11
    } else if (A.getValue() == 12) {
        value_string = "Queen"; // Queen = Value 12
    } else if (A.getValue() == 13) {
        value_string = "King";  // King = Value 13
    } else {
        value_string = to_string(A.getValue());  // Normal print
    }

    out << value_string << " of " << suit_string << "s.";
    return out;
}

// LinkedList Node
class Node {

public:
    Card card;
    Node* next;

    // Constructor: Initializes a node and clears next pointer
    Node(Card c) : card(c), next(nullptr) {}
};

// Deck Class with Linked List
class Deck {
public:
    // Constructor: Initializes an empty deck and fills it with cards
    Deck();

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

// Deck class constructor
Deck::Deck() {
    first_card = nullptr;

    // Initialize the deck from Ace to King following club-diamond-heart-spade
    for (int s = 4; s >= 1; s--) {
        for (int v = 13; v >= 1; v--) {
            Card newCard(v, s);
            Node* newNode = new Node(newCard);
            newNode->next = first_card;
            first_card = newNode;
        }
    }
}

// Output operator
ostream &operator<<(ostream &out, const Deck &A) {
    Node* current = A.first_card;
    while (current) {
        out << current->card << endl;
        current = current->next;
    }
    return out;
}

// Shuffle the cards in the deck.
void Deck::shuffle() {
    // random number generator
    srand(static_cast<unsigned>(time(nullptr)));

    // temporary vector to store cards while shuffling
    vector<Card> temp;

    // start with first card
    Node* current = first_card;

    while (current) {
        temp.push_back(current->card);
        current = current->next;
    }

    // rearrange the order randomly
    random_shuffle(temp.begin(), temp.end());
    current = first_card;

    // Copy the shuffled cards from vector and updates deck
    for (Card& card : temp) {
        current->card = card;
        current = current->next;
    }
}

int main() {
    // Creates deck class, and initializes
    Deck deck;
    cout << "Cards in the deck before shuffling: \n" << endl;
    cout << deck;

    // Shuffles the deck
    deck.shuffle();

    cout << "\nCards in the deck after shuffling:" << endl;
    cout << deck;

}
