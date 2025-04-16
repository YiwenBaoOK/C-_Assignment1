#include "ChestCard.h"
#include "Game.h"
#include "Player.h"
#include "Card.h"

void ChestCard::willAddToBank(Game& game, Player& player) {
    // Check if the player banked a KeyCard as well this turn
    const CardCollection& playArea = player.getPlayArea();
    bool hasKey = false;
    int bankedCount = 0;

    for (Card* card : playArea) {
        if (card ->getType() == CardType::Key) {
            hasKey = true;
        }
        ++bankedCount;
    }

    if (hasKey) {
        std::cout << "Chest and Key activated.  " << bankedCount << std::endl;
        for (int i = 0; i < bankedCount; ++i) {
            Card* drawn = game.drawFromDiscard();
            if (drawn) {
                std::cout << "Added " << drawn->str() << "to your bank." << std::endl;
                player.addToBank(drawn);
            }
            else {
                std::cout << "No more cards in discard pile." << std::endl;
                break;
            }
        }
    }
}
