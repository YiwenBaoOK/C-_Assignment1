#include "Card.h"
#include <random>

Card::Card(CardType t, int v) : cardtype(t), value(v) {}
Card::~Card() {}

int Card::getValue() const {
    return value;
}

CardType Card::getType() const {
    return cardtype;
}

const CardType& Card::type() const {
    return cardtype;  // Returns a reference to the card's type
}

void shuffleDeck(CardCollection& cards) {
    CardCollection shuffleDeck{ cards.begin(), cards.end() }; 
    std::shuffle(shuffleDeck.begin(), shuffleDeck.end(), std::mt19937{ std::random_device{}() }); 
    std::copy(shuffleDeck.begin(), shuffleDeck.end(), cards.begin()); 
}