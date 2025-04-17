#pragma once
#include <iostream>
#include <vector>
#include <string>

class Game;
class Player;

enum class CardType {
    Cannon, Chest, Key, Anchor, Sword, Hook, Oracle, Map, Mermaid, Kraken
};

/**
 * The Base Card class representing a playing card in the game.
 * This is an abstract class that defines the interface for all card types.
 */

class Card {
protected:
    int value;
    CardType cardtype;
public:
    //Constructor and Destructor for the card.
    Card(CardType t, int v);
    virtual ~Card();

    int getValue() const;
    bool isSameType(const Card& other) const;
    CardType getType() const;

    /**
    * Checks if this card's value is higher than another card of the same type
    * @param other The card to compare with
    * @return true if this card has higher value and same type, false otherwise
    */
    bool isHigherValueThan(const Card& other) const;

    /**
    * Validates if the card's value is within the acceptable range for its type
    * @return true if the card has a valid value, false otherwise
    */
    bool isValidValue() const;

    // Presents card info to screen
    virtual void present() const = 0;

    /**
     * Executes the special ability of this card when played
     * @param game Reference to the game instance
     * @param player Reference to the player who played the card
     */
    virtual void play(Game& game, Player& player) = 0;

    /**
    * Called before a card is added to a player's bank
    * Allows cards to perform special actions when banked
    * @param game Reference to the game instance
    * @param player Reference to the player who is banking the card
    */
    virtual void willAddToBank(Game& game, Player& player) {};

    /**
         * Returns a string representation of the card
         * @return A string describing the card type and value
         */
    virtual std::string str() const = 0;

};

typedef std::vector<Card*> CardCollection;
