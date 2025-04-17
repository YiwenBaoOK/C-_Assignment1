#include "HookCard.h"
#include "Player.h"
#include "Game.h"
#include <iostream>

void HookCard::play(Game& game, Player& player) {
    CardCollection& bank = player.accessBank();

    if (bank.empty()) {
        std::cout << player.getName() << "'s bank is empty. Hook card has no effect." << std::endl;
        return;
    }
        
    // Find highest value card
    Card* highest = nullptr;
    for (Card* c : bank) {
        if (!highest || c->getValue() > highest->getValue()) {
            highest = c;
        }
    }

    if (highest) {
        player.removeFromBank(highest);
        std::cout << player.getName() << " used Hook to play " << highest->str() << " from the bank into their play area." << std::endl;
        player.playCard(highest, game);
    }
}
