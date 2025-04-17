#pragma once
#include "Card.h"
#include "Game.h"
#include "Player.h"

class OracleCard : public Card {
public:
    OracleCard(int value) : Card(CardType::Oracle, value) {}

    void present() const override {
        std::cout << "Oracle(" << value << ")" << std::endl;
    }

    void play(Game& game, Player& player);

    std::string str() const override;
};

