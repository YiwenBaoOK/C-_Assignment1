#pragma once
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
        virtual void present() const = 0;
};

