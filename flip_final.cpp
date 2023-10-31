#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <ctime>
#include <algorithm>
#include <limits>

#include "Card.h"
#include "Node.h"
#include "Deck.h"

using namespace std;

// Card Class: Constructor
Card::Card(int v, int s) {
    value = v;
    suit = s;
}

Card::Card(const Card& A) {
    value = A.getValue();
    suit = A.getSuit();
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

// Card Class: Assignment operator
Card& Card::operator=(const Card& A) {
    value = A.getValue();
    suit = A.getSuit();
    return *this;
}

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

// Deck Class: Destructor
Deck::~Deck() {
    Node* current = first_card;
    while(current) {
        Node* nextCard = current->next;
        delete current;
        current = nextCard;
    }
    first_card = nullptr;
}

// Deck Class: Deal
Card Deck::deal() {
    Card topCard = first_card->card;
    Node* nextCard = first_card->next;
    delete first_card;
    first_card = nextCard;
    return topCard;
}

// Deck Class: Replace
void Deck::replace(const Card& A) {
    Node* current = first_card;
    Node* newNode = new Node(A);
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
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

int checkInput() {
    int userInput;
    cin >> userInput;
    while (!(userInput == 1 || userInput == 2)) {
        if (cin.fail()) {
            cout << "Please enter a '1' for yes or a '2' for no: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> userInput;
        }
        else {
            cout << "Please enter a '1' for yes or a '2' for no: ";
            cin >> userInput;
        }
    }
    return userInput;
}

void playFlip(Deck& d) {
    cout << "Welcome to Flip!" << endl;
    int userInput;
    cout << "Would you like to hear the rules of the game? (enter '1' for yes, '2' for no): ";
    userInput = checkInput();
    cout << endl;
    if (userInput == 1) {
        cout << "You will be dealt 24 cards from a shuffled deck, and you will be able to flip them over one at a time." << endl;
        cout << "The goal of the game is to get as many points as possible! This is how points are awarded: " << endl;
        cout << "\t10 points for an Ace.\n\t5 points for a King, Queen, or Jack.\n\t0 points for an 8, 9, or 10" << endl;
        cout << "\tlose half your points for a 7.\n\tlose all your points for a 2, 3, 4, 5, or 6.\n\tAnd recieve 1 bonus point for any heart." << endl;
        cout << "You will have the opportunity to end the game after any flip and keep your score.";
    }
    cout << endl << endl << "Okay, let's play!" << endl << endl;
    cout << "Top 24 Cards: " << endl;
    Node* firstCard = nullptr;
    for (int i = 1; i <= 24; i++) {
        Node* newNode = new Node(d.deal());
        newNode->next = firstCard;
        firstCard = newNode;
    }
    Node* current = firstCard;
    int i = 1;
    while (current) {
        cout << "Card " << i << ": " << current->card << endl;
        current = current->next;
        i++;
    }
    cout << endl << "Remaining cards in the deck: " << endl << d << endl;
    i = 0;
    int userScore = 0;
    userInput = 1;
    while(userInput == 1) {
        cout << "You drew: " << firstCard->card << " ";
        if (firstCard->card.getValue() == 1) {
            cout << "You get 10 points!" << endl;
            userScore += 10;
        }
        else if (firstCard->card.getValue() <= 6) {
            cout << "You lost all of your points. . ." << endl;
            userScore = 0;
        }
        else if (firstCard->card.getValue() == 7) {
            cout << "You lost half your points." << endl;
            userScore /= 2;
        }
        else if (firstCard->card.getValue() <= 10) {
            cout << "Your score doesn't change." << endl;
        }
        else {
            cout << "You get 5 points." << endl;
            userScore += 5;
        }
        if (firstCard->card.getSuit() == 3) {
            cout << "You drew a heart, so you get 1 bonus point!" << endl;
            userScore += 1;
        }
        d.replace(firstCard->card);
        i++;
        if (i >= 24) {
            cout << "That was the last card, the game is over." << endl << "Your final score was: " << userScore << endl;
            break;
        }
        firstCard = firstCard->next;
        cout << "Current Hand: " << endl;
        Node* current = firstCard;
        for (int j = 24; j > i; j--) {
            cout << current->card << endl;
            current = current->next;
        }
        cout << "Your current score is: " << userScore << endl;
        cout << "Cards left: " << 24-i << endl;
        cout << "Would you like to draw another card? (enter '1' for yes, '2' for no) ";
        userInput = checkInput();
        cout << endl << endl;
    }
    if (i < 24) {
        cout << "You exited with a final score of " << userScore << endl;
    }
    cout << "Thank you for playing!" << endl;
}

int main() {
    // Creates deck class, and initializes
    Deck* deck = new Deck();

    deck->shuffle();
    deck->shuffle();
    deck->shuffle();

    playFlip(*deck);
}