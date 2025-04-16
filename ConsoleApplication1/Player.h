#include <vector>
#include "Card.h"

class Player {
private:
    std::string _name;
    int _score;
    CardCollection playArea;  // Cards in the play area
    CardCollection bank;      // Cards in the player's bank



public:
    Player();
    std::string getName() const;
    void setName(const std::string& name);
    int getScore() const;
    void setScore(int score);

    // Methods to manage cards in the play area and bank
    bool playCard(Card* card, Game& game);
    void addToBank(Card* card);
    void removeFromBank(Card* card);
    void printBank() const;

    const CardCollection& getPlayArea() const;// To access the player's PlayArea
    const CardCollection& getBank() const; // To access the player's bank safely without editing
    CardCollection& getBank();             // To access and modify the player's bank safely without editing


};
