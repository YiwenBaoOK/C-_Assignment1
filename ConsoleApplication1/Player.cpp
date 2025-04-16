
#include "Player.h"
#include "Game.h"
#include <iostream>
#include <algorithm>

// Constructor: Initialize the player's name randomly and score to 0
Player::Player() : _score(0) {
    std::string names[] = { "Sam", "Billy", "Jen", "Bob", "Sally", "Joe", "Sue", "Sasha", "Tina", "Marge" };
    _name = names[rand() % 10];  // Randomly assign a name from the list
}

// Getter for player's name
std::string Player::getName() const {
    return _name;
}

// Setter for player's name
void Player::setName(const std::string& name) {
    _name = name;
}

// Getter for player's score
int Player::getScore() const {
    return _score;
}

// Setter for player's score
void Player::setScore(int score) {
    _score = score;
}

// Add a card to the bank
void Player::addToBank(Card* card) {
    if (card) {
        bank.push_back(card);  // This works if bank is of type CardCollection (vector<Card*>)
        std::cout << _name << " added " << card->str() << " to their bank." << std::endl;
    }
}

// Remove a card from the bank
void Player::removeFromBank(Card* card) {
    auto it = std::find(bank.begin(), bank.end(), card);  // Find the card in the bank
    if (it != bank.end()) {
        bank.erase(it);  // Remove the card if found
        std::cout << _name << " removed " << card->str() << " from their bank." << std::endl;
    }
}

// For Reading the bank safely
void Player::printBank() const {
    std::cout << _name << "'s bank:" << std::endl;
    for (const Card* c : bank) {
        std::cout << c->str() << std::endl;  // Print each card's string representation
    }
}

// Getter for the bank collection
const CardCollection& Player::getBank() const {
    return bank;
}

// Allows modfiying the bank
CardCollection& Player::getBank() {
    return bank;
}


// Play a card into the play area (from deck to player)
bool Player::playCard(Card* card, Game& game) {
    // For now, simply add the card to the play area
    playArea.push_back(card);

    // Check if the card causes a "bust" (duplicate card in play area)
    // If a duplicate card is found, it is a "bust" and the player loses
    for (size_t i = 0; i < playArea.size(); ++i) {
        for (size_t j = i + 1; j < playArea.size(); ++j) {
            if (playArea[i]->getType() == playArea[j]->getType()) {
                std::cout << _name << " has busted! Duplicate card: " << playArea[i]->str() << std::endl;
                return true;  // Bust detected, return true
            }
        }
    }
    return false;  // No bust
}
