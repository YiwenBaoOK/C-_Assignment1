#pragma once
#include "Card.h"
class KrakenCard :
    public Card
{public:
    KrakenCard(int value) : Card(CardType::Kraken, value) {}
    void play(Game& game, Player& player) override {
        //Kraken card doesn't have any ability but worths more points.
        std::cout << " No effect but Mermaids are worth more." << std::endl;
    }
    void present() const override {
        std::cout << "Kraken(" << value << ")" << std::endl;
    }
    std::string str() const override {
        return "Kraken(" + std::to_string(value) + ")";
    }
};

