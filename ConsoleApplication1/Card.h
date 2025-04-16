#include <iostream>
#include <vector>
#include <string>

class Game;
class Player;

enum class CardType {
    Cannon, Chest, Key, Anchor, Sword, Hook, Oracle, Map, Mermaid, Kraken
};


class Card {
protected:
    int value;
    CardType cardtype;
public:
    Card(CardType t, int v);
    virtual ~Card();

    int getValue() const;
    CardType getType() const;
    const CardType& type() const;

    // Presents card type to screen
    virtual void present() const = 0;

    // Play the effect of this card
    virtual void play(Game& game, Player& player) = 0;

    // Optional: Called before being added to bank
    virtual void willAddToBank(Game& game, Player& player) {}

    // Returns a string representation of card type and value
    virtual std::string str() const = 0;
};

typedef std::vector<Card*> CardCollection;
