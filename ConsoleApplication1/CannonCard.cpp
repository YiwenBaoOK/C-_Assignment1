#include "CannonCard.h"
#include "Player.h"
#include "Game.h"

void CannonCard::play(Game& game, Player& player) {
    Player& opponent = game.getOpponent(player);
    CardCollection& opponentBank = opponent.getBank();

    if (opponentBank.empty()) {
        std::cout << "Opponent's bank is empty. No card to discard." << std::endl;
        return;
    }

    // Find the highest value card
    auto highestCardIt = std::max_element(opponentBank.begin(), opponentBank.end(),
        [](Card* a, Card* b) {
            return a->getValue() < b->getValue();
        });

    if (highestCardIt != opponentBank.end()) {
        Card* highestCard = *highestCardIt;
        opponentBank.erase(highestCardIt); // remove from bank
        game.discardCard(highestCard);     // add to discard pile

        std::cout << "Cannon effect: Discarded " << highestCard->str()
            << " from " << opponent.getName() << "'s bank." << std::endl;
    }

}