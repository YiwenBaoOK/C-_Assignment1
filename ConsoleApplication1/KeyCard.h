#pragma once
#include "Card.h"
#include <iostream>

class KeyCard : public Card {
public:
    KeyCard(int value) : Card(CardType::Key, value) {}

    void play(Game& game, Player& player) override {
        // No immediate effect
        std::cout << "No immediate effect. If banked with a chest, draw as many bonus cards from the Discard pile as you moved into your Bank." << std::endl;
    }

    void willAddToBank(Game& game, Player& player) override;

    void present() const override {
        std::cout << "Key(" << value << ")" << std::endl;
    }

    std::string str() const override {
        return "Key(" + std::to_string(value) + ")";
    }
};

