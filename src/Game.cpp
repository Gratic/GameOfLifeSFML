//
// Created by Fraxinus on 19/11/2019.
//

#include "Game.h"
#include "Grid.h"
#include "Cell.h"
#include "vector"
#include "SFML/Graphics.hpp"

Grid& Game::getGrid() {
    return grid;
}

void Game::setGrid(const Grid &grid) {
    Game::grid = grid;
}

const sf::Vector2f &Game::getPosition() {
    return position;
}

void Game::setPosition(const sf::Vector2f &position) {
    Game::position = position;
}

const sf::Vector2f &Game::getNumberOfCells() {
    return numberOfCells;
}

void Game::setNumberOfCells(const sf::Vector2f &numberOfCells) {
    Game::numberOfCells = numberOfCells;
}

const sf::Vector2f &Game::getSizeOfCells() {
    return sizeOfCells;
}

void Game::setSizeOfCells(const sf::Vector2f &sizeOfCells) {
    Game::sizeOfCells = sizeOfCells;
}

bool Game::isPlay() {
    return play;
}

void Game::setPlay(bool play) {
    Game::play = play;
}

Game::Game(const sf::Vector2f &position, const sf::Vector2f &numberOfCells, const sf::Vector2f &sizeOfCells, bool play)
        : position(position), numberOfCells(numberOfCells), sizeOfCells(sizeOfCells), play(play), grid(numberOfCells, position, sizeOfCells) {
    srand(time(NULL));
    grid.generateGrid();
    grid.findNeighbors();
}

void Game::gameOfLife() {
    std::vector<std::vector<Cell>> cells(grid.getCells());
    for (int i(0); i < numberOfCells.x; i++) {
        for (int j(0); j < numberOfCells.y; j++) {
            int neighbors = grid.getCells()[i][j].numberOfNeighbors(1);
            int status = grid.getCells()[i][j].getStatus();

            if(status == 1 && neighbors < 2)
                cells[i][j].setStatus(0);
            else if(status == 1 && neighbors > 3)
                cells[i][j].setStatus(0);
            else if(status == 1 && (neighbors == 2 || neighbors == 3))
                cells[i][j].setStatus(1);
            else if(status == 0 && neighbors == 3)
                cells[i][j].setStatus(1);
        }
    }

    grid.setCells(cells);
    grid.findNeighbors();
}
