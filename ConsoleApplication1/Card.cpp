#include "Card.h"

Card::Card(CardType t, int v) : cardtype(t), value(v) {
    //Needs to validate card value when creating card.
    if (!isValidValue()) {
        throw std::invalid_argument("Invalid card Value for this card type");
    }
}

Card::~Card() {}

int Card::getValue() const {
    return value;
}


bool Card::isSameType(const Card& other) const {
    return cardtype == other.cardtype;
}
CardType Card::getType() const {
    return cardtype;
}

bool Card::isHigherValueThan(const Card& other) const {
    // Cards must be of the same type to compare values
    if (cardtype != other.cardtype) {
        return false;
    }

    return value > other.value;
}

bool Card::isValidValue() const {
    // Most cards have values from 2 to 7
    if (cardtype != CardType::Mermaid && (value < 2 || value > 7)) {
        return false;
    }

    // Mermaid cards have values from 4 to 9
    if (cardtype == CardType::Mermaid && (value < 4 || value > 9)) {
        return false;
    }

    return true;
}


