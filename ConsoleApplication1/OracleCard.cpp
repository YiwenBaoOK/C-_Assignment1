#include "OracleCard.h"

void OracleCard::play(Game& game, Player& player) {
    std::cout << player.getName() << " played an Oracle card: " << str() << std::endl;

    // Peek logic: look at the top card of the deck
    Card* topCard = game.peekDeck();
    if (topCard) {
        std::cout << player.getName() << " peeked at the next card: " << topCard->str() << std::endl;
    }
    else {
        std::cout << "The deck is empty. Nothing to peek at." << std::endl;
    }


    Card* nextCard = game.peekDeck();
    if (!nextCard) {
        std::cout << "Not enough cards in the deck. " << player.getName() << "'s turn ends." << std::endl;

        const CardCollection& playArea = player.getPlayArea();
        for (Card* card : playArea) {
            player.addToBank(card);
        }
        return;
    }

    std::cout << "Next card in the deck is: " << nextCard->str() << std::endl;
    std::cout << "Do you want to draw this card? (y/n): ";
    char choice;
    std::cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        game.drawCardForPlayer(player); // Must be implemented in Game.cpp
    }
    else {
        std::cout << player.getName() << " chose not to draw. Turn ends." << std::endl;
        const CardCollection& playArea = player.getPlayArea();
        for (Card* card : playArea) {
            player.addToBank(card);
        }
    }
}

std::string OracleCard::str() const {
    return "Oracle(" + std::to_string(value) + ")";
}