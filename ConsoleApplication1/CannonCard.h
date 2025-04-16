#pragma once
#include "Card.h"
class CannonCard : public Card {
public:
    CannonCard(int v);
    void present() const override;
    void play(Game& game, Player& player) override;
    std::string str() const override;
};

