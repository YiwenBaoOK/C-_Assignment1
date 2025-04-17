#pragma once
#include "Card.h"
class MapCard :
    public Card
{
    void present() const override {
        std::cout << "Map(" << value << ")" << std::endl;
    }
    std::string str() const override {
        return "Map(" + std::to_string(value) + ")";
    }
};

