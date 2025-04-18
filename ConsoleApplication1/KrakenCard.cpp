#include "KrakenCard.h"
#include "Player.h"
#include "Game.h"

void KrakenCard::play(Game& game, Player& player) {
    std::cout << player.getName() << " played a Kraken card: " << str() << std::endl;

    for (int i = 0; i < 3; ++i) {
        Card* drawnCard = game.drawCard();
        if (!drawnCard) {
            std::cout << "No more cards to draw. Turn ends." << std::endl;
            break;
        }

        bool busted = player.playCard(drawnCard, game);
        if (busted) {
            // Handle bust directly here
            std::cout << "BUST! " << player.getName() << " loses all cards in play area." << std::endl;

            // Discard all cards in play area
            const CardCollection& playArea = player.getPlayArea();
            for (Card* card : playArea) {
                game.discardCard(card);
            }

            // Clear the play area
            player.clearPlayArea(false);
            break;
        }
        else {
            std::cout << drawnCard << std::endl;
        }
    }
}
// No bust occurred during Kraken's ability
