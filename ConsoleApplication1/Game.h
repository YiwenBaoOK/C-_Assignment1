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
    std::vector<std::unique_ptr<Player>> players;
    std::stack<Card*> deck;
    CardCollection discardPile;
    int currentTurn;
    int round;
    int currentPlayerIndex;
    const int maxTurns = 20;

public:
    Game();
    ~Game();

    //Is responsible for initialising and starting a new game.
    void startGame();

    //Is responsible for ending a game and printing final scores.
    void endGame();

    //Is responsible for creating the card deck.
    void createDeck();

    //Is responsible for shuffling the deck.
    void shuffleDeck();

    //Is responsible for controlling a turn in the game.
    void takeTurn();

    Card* drawCard();
    void discardCard(Card* card);

    //Is responsible for initialising players.
    Player& getCurrentPlayer();
    Player& getOpponent(Player& current);

    //Getting the current turn of the game.
    int getCurrentTurn() const;

    //Getting the current round of the game.
    int getRound() const;

    //Determine if the game is over.
    bool isGameOver() const;

    Card* drawFromDiscard();  // Returns the top card from the discard pile

};
