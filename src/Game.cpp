#include "D:\PBL2_GAMESTORE\include\Game.h"
#include "D:\PBL2_GAMESTORE\include\FileManager.h"
#include <iostream>

Game::Game(int idGame, std::string nameGame, std::string genre, double priceGame, int gamesInStock)
{
    this->idGame = idGame;
    this->nameGame = nameGame;
    this->genre = genre;
    this->priceGame = priceGame;
    this->gamesInStock = gamesInStock;
}


Game::Game() {};

int Game::getIdGame()
{
    return idGame;
}

std::string Game::getNameGame()
{
    return nameGame;
}

std::string Game::getGenre()
{
    return genre;
}

double Game::getPriceGame()
{
    return priceGame;
}

int Game::getGamesInStock()
{
    return gamesInStock;
}

void Game::setGamesInStock(int stock)
{
    this->gamesInStock = stock;
}

void Game::displayGame()
{
    int gameSize;
    Game *games = FileManager::loadGames("D:\\PBL2_GAMESTORE\\text\\Games.txt", gameSize);

    if (games == NULL || gameSize == 0) {
        std::cout << "No game available. " << std::endl;
        return;
    }
    
    // Hiển thị danh sách game
    std::cout << "Available games: " << std::endl;
    std::cout << "GameID\t" << "gameName\t" << "Genre\t" << "PriceGame\t" << "gamesInStock" << std::endl;
    for (int i = 0; i < gameSize; i++) {
        std::cout << games[i].getIdGame() << "\t" << games[i].getNameGame() << "\t" << games[i].getGenre() << "\t"
                  << games[i].getPriceGame() << "\t" << games[i].getGamesInStock() << std::endl;
    }
    // Giải phóng bộ nhớ
    delete [] games;
}