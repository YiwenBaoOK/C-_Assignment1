#pragma once
#include "Card.h"
class ChestCard : public Card {
public:
    ChestCard(int value) : Card(CardType::Chest, value) {}

    void play(Game& game, Player& player) override {
        // No immediate effect
        std::cout << "No immediate effect. If banked with a key, draw as many bonus cards from the Discard pile as you moved into your Bank" << std::endl;
    }

    void willAddToBank(Game& game, Player& player) override;

    void present() const override {
        std::cout << "Chest(" << value << ")" << std::endl;
    }

    std::string str() const override {
        return "Chest(" + std::to_string(value) + ")";
    }
};

