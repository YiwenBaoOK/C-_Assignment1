#pragma once
#include "Card.h"

class SwordCard : public Card {
public:
    SwordCard(int value) : Card(CardType::Sword, value) {}

    void play(Game& game, Player& player) override;

    void present() const override {
        std::cout << "Sword(" << value << ")" << std::endl;
    }

    std::string str() const override {
        return "Sword(" + std::to_string(value) + ")";
    }
};
