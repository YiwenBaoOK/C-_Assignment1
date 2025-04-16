#include "KeyCard.h"
#include "Game.h"
#include "Player.h"

void KeyCard::play(Game& game, Player& player) {
    std::cout << "Key has no immediate effect." << std::endl;
}

void KeyCard::willAddToBank(Game& game, Player& player) {
    // Do nothing here. Chest handles the combo logic.
}
