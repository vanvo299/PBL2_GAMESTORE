#ifndef GAME_H
#define GAME_H

#include <string>

class Game {
private:
    int idGame;
    std::string nameGame;
    std::string genre;
    double priceGame;
    int gamesInStock;
public:
    Game(int idGame, std::string nameGame, std::string genre, double priceGame, int gamesInStock);
    Game();
    // Getter
    int getIdGame();
    std::string getNameGame();
    std::string getGenre();
    double getPriceGame();
    int getGamesInStock();

    // Setter
    void setGamesInStock(int stock);
    void displayGame();
};
#endif