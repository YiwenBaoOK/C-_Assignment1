#pragma once
#include "Card.h"
class HookCard :
    public Card{
    public:
    HookCard(int value) : Card(CardType::Hook, value) {}

    void play(Game& game, Player& player) override;
    void present() const override {
        std::cout << "Hook(" << value << ")" << std::endl;
    }
    std::string str() const override {
        return "Hook(" + std::to_string(value) + ")";
    }
    
};

