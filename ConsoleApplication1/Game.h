#pragma once
#include <vector>
#include <stack>
#include <memory>
#include <random>
#include "Player.h"

#define GAME_TITLE \
"______                  _   ___  ___              _     \n" \
"|  _  \\                | |  |  \\/  |             ( )    \n" \
"| | | | ___   __ _   __| |  | .  . |  __ _  _ __ |/ ___ \n" \
"| | | |/ _ \\ / _` | / _` |  | |\\/| | / _` || '_ \\  / __|\n" \
"| |/ /|  __/| (_| || (_| |  | |  | || (_| || | | | \\__ \\ \n" \
"______ \\___| \\__,_| \\__,_|  \\_|  |_/ \\__,_||_| |_| |___/\n" \
"|  _  \\                         _      _\n" \
"| | | | _ __  __ _ __      __ _| |_  _| |_\n" \
"| | | || '__|/ _` |\\ \\ /\\ / /|_   _||_   _|\n" \
"| |/ / | |  | (_| | \\ V  V /   |_|    |_|\n" \
"|___/  |_|   \\__,_|  \\_/\\_/\n"

class Game {
private:
    // Game state variables
    std::vector<std::unique_ptr<Player>> players;     // Players in the game
    std::stack<Card*> deck;                          // Deck of cards
    CardCollection discardPile;                      // Discard pile for busted cards
    int currentTurn;                                 // Current turn number
    int round;                                       // Current round number
    int currentPlayerIndex;                          // Index of the active player
    const int maxTurns = 20;                         // Maximum number of turns before game ends

public:
    // Constructor and destructor
    Game();                                         // Initialize game state
    ~Game();                                        // Clean up resources

    // Game flow methods
    void startGame();                               // Initialize and start a new game
    void endGame();                                 // End game and display final scores
    void takeTurn();                                // Handle a single player's turn
    bool isGameOver() const;                        // Check if game should end

    // Deck management methods
    void createDeck();                              // Create a new deck with 54 cards
    void shuffleDeck();                             // Shuffle the deck randomly
    Card* drawCard();                               // Draw top card from deck
    Card* peekDeck();                               // Look at top card without removing
    void discardCard(Card* card);                   // Add card to discard pile
    Card* drawFromDiscard();                        // Draw top card from discard pile

    // Card manipulation methods
    void drawCardForPlayer(Player& player);         // Draw card for specific player

    // Player management methods
    Player& getCurrentPlayer();                     // Get reference to current player
    Player& getOpponent(Player& current);           // Get reference to opponent player

    // Game state access methods
    int getCurrentTurn() const;                     // Get current turn number
    int getRound() const;                           // Get current round number

    // Helper methods for game logic
    bool checkForBust(const Player& player);         // Check if player has duplicate card types

    void bankCards(Player& player);                  // Move cards from play area to bank

    int calculateFinalScore(const Player& player);   // Calculate final score based on highest card of each suit

    //Is responsible for initialising players.
    Player& getCurrentPlayer();
    Player& getOpponent(Player& current);

    //Getting the current turn of the game.
    int getCurrentTurn() const;

    //Getting the current round of the game.
    int getRound() const;
};
