#pragma once
#include "Card.h"
class CannonCard : public Card {
public:
    CannonCard(int value) : Card(CardType::Cannon, value) {}

    void play(Game& game, Player& player) override;
    void present() const override {
        std::cout << "Cannon(" << value << ")" << std::endl;
    }
    std::string str() const override {
        return "Cannon(" + std::to_string(value) + ")";
    }
};


