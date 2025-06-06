#include "Game.h"
#include "CannonCard.h"
#include "ChestCard.h"
#include "KeyCard.h"
#include "SwordCard.h"
#include "HookCard.h"
#include "OracleCard.h"
#include "MapCard.h"
#include "MermaidCard.h"
#include "KrakenCard.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <string>
#include <map>

Game::Game() : currentTurn(0), round(1), currentPlayerIndex(0) {
    // Initialize an empty game
}

Game::~Game() {
    // Clean up any remaining cards in the deck
    while (!deck.empty()) {
        Card* card = deck.top();
        deck.pop();
        delete card;
    }

    // Clean up cards in the discard pile
    for (Card* card : discardPile) {
        delete card;
    }
    discardPile.clear();

    // Players are managed by unique_ptr so they will be automatically deleted
}

void Game::startGame() {
    
    std::cout << GAME_TITLE << std::endl;
    std::cout << "Starting Dead Man's Draw++!" << std::endl;

    // Create two players with randomly generated names
    players.clear();
    players.push_back(std::make_unique<Player>());
    players.push_back(std::make_unique<Player>());

    // Reset game state
    currentTurn = 0;
    round = 1;
    currentPlayerIndex = 0;

    // Clear the discard pile
    discardPile.clear();

    // Create and shuffle the deck
    std::vector<Card*> newCards = createDeck();

    // Clear the existing deck
    while (!deck.empty()) {
        deck.pop();
    }

    // Shuffle the new cards
    std::shuffle(newCards.begin(), newCards.end(), std::mt19937{ std::random_device{}() });

    // Transfer cards to the deck (stack)
    for (auto it = newCards.rbegin(); it != newCards.rend(); ++it) {
        deck.push(*it);
    }

    std::cout << "Deck initialized with " << deck.size() << " cards." << std::endl;

    std::cout << "\nGame started! " << players[0]->getName() << " vs " << players[1]->getName() << "\n" << std::endl;

    // Start the game loop
    while (!isGameOver()) {
        takeTurn();

        // Move to the next player
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();

        // Update turn and round counters
        currentTurn++;
        if (currentTurn >= players.size()) {
            currentTurn = 0;
            round++;
        }
    }

    endGame();
}

void Game::endGame() {
    std::cout << "\n======= Game Over =======\n" << std::endl;
    std::cout << "Final Scores:" << std::endl;

    int winnerScore = -1;
    int winnerIndex = -1;

    for (size_t i = 0; i < players.size(); ++i) {
        const auto& player = players[i];
        int playerScore = player->getScore();

        std::cout << player->getName() << ": " << playerScore << " points" << std::endl;

        if (playerScore > winnerScore) {
            winnerScore = playerScore;
            winnerIndex = static_cast<int>(i);
        }
    }

    if (winnerIndex != -1) {
        std::cout << "\nThe winner is " << players[winnerIndex]->getName() << "!" << std::endl;
    }
    else {
        std::cout << "\nIt's a tie!" << std::endl;
    }

    std::cout << "\nThanks for playing Dead Man's Draw++!" << std::endl;
}

std::vector<Card*> Game::createDeck() {
    std::vector<Card*> newDeck;
    // Create Cannon cards
    for (int value = 2; value <= 7; ++value) {
        newDeck.push_back(new CannonCard(value));
    }

    // Create Chest cards
    for (int value = 2; value <= 7; ++value) {
        newDeck.push_back(new ChestCard(value));
    }

    // Create Key cards
    for (int value = 2; value <= 7; ++value) {
        newDeck.push_back(new KeyCard(value));
    }

    // Create Sword cards
    for (int value =2; value <= 7; ++value) {
        newDeck.push_back(new SwordCard(value));
    }

    //Create Hook Cards
    for (int value = 2; value <= 7; ++value) {
        newDeck.push_back(new HookCard(value));
    }

    // Create Oracle cards
    for (int value = 2; value <= 7; ++value) {
        newDeck.push_back(new OracleCard(value));
    }

    // Create Map cards
    for (int value = 2; value <= 7; ++value) {
        newDeck.push_back(new MapCard(value));
    }

    // Create Mermaid cards
    for (int value = 4; value <= 9; ++value) {
        newDeck.push_back(new MermaidCard(value));
    }

    // Create Kraken cards
    for (int value = 2; value <= 7; ++value) {
        newDeck.push_back(new KrakenCard(value));
    }
    return newDeck;
}  
// Convert the stack to a vector for shuffling
void Game::shuffleDeck(CardCollection& cards)
{
    CardCollection shuffleDeck{ cards.begin(), cards.end() };
    std::shuffle(shuffleDeck.begin(), shuffleDeck.end(), std::mt19937{ std::random_device{}() });
    std::copy(shuffleDeck.begin(), shuffleDeck.end(), cards.begin());
}

void Game::takeTurn() {
    Player& currentPlayer = getCurrentPlayer();

    // Announce Round and Turn number
    std::cout << "\nRound " << round << " Turn " << currentTurn + 1 << std::endl;

    // Display player name and their Bank
    currentPlayer.printBank();

    bool continueTurn = true;

    while (continueTurn) {
        // Draw a card from the deck
        Card* drawnCard = drawCard();

        if (!drawnCard) {
            std::cout << "No more cards available!" << std::endl;
            break;
        }

        bool bust = currentPlayer.playCard(drawnCard, *this);

        if (bust) {
            std::cout << "BUST! " << currentPlayer.getName() << " loses all cards in play area." << std::endl;
            //// Display player point from their Bank
            displayCurrentPlayerScore();
            // Discard the drawn card
            discardCard(drawnCard);

            // Discard all cards in the player's play area, add them to the discard pile.
            const CardCollection& playArea = currentPlayer.getPlayArea();
            for (Card* card : playArea) {
                discardCard(card);
                discardPile.push_back(card);
            }
            // Clear the player's play area without deleting the cards (already in discard pile)
            currentPlayer.clearPlayArea(false);
            // End the turn for this player
            break;
        }
        else {
            // If not bust, execute card ability
            drawnCard->play(*this, currentPlayer);

            // Display the current play area
            std::cout << "Play Area: ";
            for (const Card* card : currentPlayer.getPlayArea()) {
                std::cout << card->str() << " ";
            }
            std::cout << std::endl;

            // Ask if player wants to draw again
            std::string input;
            std::cout << "Draw again? (y/n): ";
            std::cin >> input;

            // Check player's response
            if (input != "y") {
                // End the turn
                continueTurn = false;

                // Bank the cards in the play area
                bankCards(currentPlayer);
                                
                //// Display player point from their Bank
                displayCurrentPlayerScore();
            }
        }
    }
}

Card* Game::drawCard() {
    if (deck.empty()) {
        // If the deck is empty, reshuffle the discard pile
        if (!discardPile.empty()) {
            std::cout << "Reshuffling the discard pile..." << std::endl;

            // Create a temporary vector for shuffling
            std::vector<Card*> tempDeck(discardPile.begin(), discardPile.end());
            discardPile.clear();

            // Shuffle the temporary deck
            std::shuffle(tempDeck.begin(), tempDeck.end(), std::mt19937{ std::random_device{}() });

            // Push cards back into the deck
            for (Card* card : tempDeck) {
                discardPile.clear();
                shuffleDeck(discardPile);
            }
        }
        else {
            // If both deck and discard pile are empty, return nullptr
            std::cout << "No more cards available!" << std::endl;
            return nullptr;
        }
    }

    // Draw the top card from the deck
    Card* drawnCard = deck.top();
    deck.pop();
    return drawnCard;
}

void Game::discardCard(Card* card) {
    discardPile.push_back(card);
}

Player& Game::getCurrentPlayer() {
    return *players[currentPlayerIndex];
}

Player& Game::getOpponent(Player& current) {
    for (auto& player : players) {
        if (player.get() != &current) {
            return *player;
        }
    }

    // This should never happen in a two-player game, but return the current player as a fallback
    return current;
}

int Game::getCurrentTurn() const {
    return currentTurn;
}

int Game::getRound() const {
    return round;
}

bool Game::checkForBust(const Player& player)
{
    return false;
}

void Game::bankCards(Player& player)
{
    const CardCollection& playArea = player.getPlayArea();

    // Move all cards from play area to bank
    for (Card* card : playArea) {
        player.addToBank(card);
    }

    // Clear the play area (without deleting the cards)
    player.clearPlayArea(false);

    std::cout << player.getName() << " banked their cards." << std::endl;
}

void Game::displayCurrentPlayerScore() {
    Player& currentPlayer = getCurrentPlayer();
    int score = calculateFinalScore(currentPlayer);

    std::cout<< currentPlayer.getName() << "'s bank: " << std::endl;
    currentPlayer.printBank();
    std::cout << "score: " << score << " points" << std::endl;
}


int Game::calculateFinalScore(const Player& player)
{
    int score = 0;
    const CardCollection& bank = player.getBank();

    // Track the highest value card of each type
    std::map<CardType, int> highestValueByType;

    // Find the highest value for each card type
    for (const Card* card : bank) {
        CardType cardType = card->getType();
        int cardValue = card->getValue();

        // Update if this is the highest value card of this type
        if (highestValueByType.find(cardType) == highestValueByType.end() ||
            cardValue > highestValueByType[cardType]) {
            highestValueByType[cardType] = cardValue;
        }
    }

    // Sum up the highest value for each card type
    for (const auto& pair : highestValueByType) {
        score += pair.second;
    }

    return score;
}

bool Game::isGameOver() const {
    // Game ends after a certain number of turns or when a player reaches a score threshold
    return round > maxTurns || deck.empty();
}

Card* Game::drawFromDiscard() {
    if (discardPile.empty()) {
        return nullptr;
    }

    Card* topCard = discardPile.back();
    discardPile.pop_back();
    return topCard;
}

Card* Game::peekDeck() {
    if (deck.empty()) {
        return nullptr;
    }
    return deck.top();
}

void Game::drawCardForPlayer(Player& player) {
    // In the simplified version, we simply draw from the deck
    Card* drawnCard = drawCard();

    if (drawnCard) {
        // Player receives the card and decides what to do with it
        // This is handled in the takeTurn method already
        // Just for compatibility with the interface
    }
}
