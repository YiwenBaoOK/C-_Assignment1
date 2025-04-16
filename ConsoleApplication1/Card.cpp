#include "Card.h"

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