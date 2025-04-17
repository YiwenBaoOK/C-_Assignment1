#include "SwordCard.h"
#include "Game.h"
#include "Player.h"

void SwordCard::play(Game& game, Player& player) {
    Player& opponent = game.getOpponent(player);
    CardCollection& opponentBank = opponent.accessBank();

    if (opponentBank.empty()) {
        std::cout << "Sword effect: Opponent's bank is empty. No card to steal." << std::endl;
        return;
    }

    auto highestCardIt = std::max_element(opponentBank.begin(), opponentBank.end(),
        [](Card* a, Card* b) {
            return a->getValue() < b->getValue();
        });

    if (highestCardIt != opponentBank.end()) {
        Card* stolenCard = *highestCardIt;
        opponentBank.erase(highestCardIt);
        std::cout << player.getName() << " steals " << stolenCard->str() << " from " << opponent.getName() << "'s bank." << std::endl;
        player.playCard(stolenCard, game);
    }
}
