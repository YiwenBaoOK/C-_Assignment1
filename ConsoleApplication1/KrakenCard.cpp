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
            // Bust logic is handled inside playCard
            break;
        }
    }
}
