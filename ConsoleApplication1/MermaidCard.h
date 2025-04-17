#pragma once
#include "Card.h"
#include <string>

class MermaidCard : public Card {
public:
    MermaidCard(int value) : Card(CardType::Mermaid, value) {};
    void play(Game& game, Player& player) override {
        //Mermaid card doesn't have any ability but worths more points.
        std::cout << " No effect but Mermaids are worth more." << std::endl;
    }

    std::string str() const override {
        return "Mermaid(" + std::to_string(value) + ")";
    }
};
