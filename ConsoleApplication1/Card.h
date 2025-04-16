#pragma once
#include <string>
#include <vector>
enum class CardType {
    Cannon, Chest, Key, Sword, Hook, Oracle, Map, Mermaid, Kraken
};
    class Card {
    protected:
        int value;
        CardType type;
    public:
        Card(CardType t, int v) : type(t), value(v) {}
        virtual ~Card() {}

        int getValue() const { return value; }
        CardType getType() const { return type; }

        //Function to return the card type.
        const CardType& type();

        //Function to return the type of card and value as a string.
        virtual std::string str() const;

        virtual void present() const;

        virtual void willAddToBank(Game& game, Player& player) {};
        typedef std::vector<Card*> CardCollection;
};

