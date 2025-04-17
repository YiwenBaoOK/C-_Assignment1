#pragma once
#include "Card.h"
class KrakenCard :
    public Card
{
    public:
    KrakenCard(int value) : Card(CardType::Kraken, value) {}
    void play(Game& game, Player& player) override;
    void present() const override {
        std::cout << "Kraken(" << value << ")" << std::endl;
    }
    std::string str() const override {
        return "Kraken(" + std::to_string(value) + ")";
    }
};

