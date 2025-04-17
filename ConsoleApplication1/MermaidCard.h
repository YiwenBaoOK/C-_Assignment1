#pragma once
#include "Card.h"
#include <string>

class MermaidCard : public Card {
public:
    MermaidCard(int value) : Card(CardType::Mermaid, value) {}
    void play(Game& game, Player& player) override;
    void present() const override {
        std::cout << "Mermaid(" << value << ")" << std::endl;
    }
    std::string str() const override {
        return "Mermaid(" + std::to_string(value) + ")";
    }
};
