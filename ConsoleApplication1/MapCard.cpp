#include "MapCard.h"
#include "Game.h"
#include <iostream>
#include <limits>

void MapCard::play(Game& game, Player& player) {
    std::cout << player.getName() << " played a Map card: " << str() << std::endl;

    std::vector<Card*> drawnCards;

    // Draw up to 3 cards from the discard pile
    for (int i = 0; i < 3; ++i) {
        Card* card = game.drawFromDiscard();
        if (!card) {
            std::cout << "No more cards in discard pile to draw." << std::endl;
            break;
        }
        drawnCards.push_back(card);
    }

    if (drawnCards.empty()) {
        std::cout << "No cards were available to draw." << std::endl;
        return;
    }

    std::cout << "Cards drawn from discard pile:" << std::endl;
    for (size_t i = 0; i < drawnCards.size(); ++i) {
        std::cout << i + 1 << ". " << drawnCards[i]->str() << std::endl;
    }

    std::cout << "Choose one card to play into your play area (1-" << drawnCards.size() << "): ";
    int choice = 0;
    while (true) {
        std::cin >> choice;
        if (std::cin.fail() || choice < 1 || choice > static_cast<int>(drawnCards.size())) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice. Please enter a number between 1 and " << drawnCards.size() << ": ";
        }
        else {
            break;
        }
    }

    Card* selected = drawnCards[choice - 1];
    drawnCards.erase(drawnCards.begin() + (choice - 1));

    std::cout << player.getName() << " chooses to play: " << selected->str() << std::endl;
    bool busted = player.playCard(selected, game);
    if (busted) {
        for (Card* c : player.getPlayArea()) {
            game.discardCard(c);
        }
    }

    // Discard the rest
    for (Card* c : drawnCards) {
        game.discardCard(c);
    }
}

