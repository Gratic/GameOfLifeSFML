//
// Created by Fraxinus on 19/11/2019.
//

#include <chrono>
#include <thread>
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
    grid.setNumberOfCells(numberOfCells);
    grid.generateGrid();
    Game::numberOfCells = numberOfCells;
}

const sf::Vector2f &Game::getSizeOfCells() {
    return sizeOfCells;
}

void Game::setSizeOfCells(const sf::Vector2f &sizeOfCells) {
    grid.setSizeOfCell(sizeOfCells);
    grid.generateGrid();
    Game::sizeOfCells = sizeOfCells;
}

bool Game::isPlay() {
    return play;
}

void Game::setPlay(bool play) {
    Game::play = play;
}

Game::Game(const sf::Vector2f &position, const sf::Vector2f &numberOfCells, const sf::Vector2f &sizeOfCells, bool play)
        : position(position), numberOfCells(numberOfCells), sizeOfCells(sizeOfCells), play(play), grid(numberOfCells, position, sizeOfCells), iteration(0) {
    srand(time(NULL));
    grid.generateGrid();
}

void Game::gameOfLife() {
    if (!play || !getGrid().isGenerated())
        return;

    grid.setInUse(true);

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

    grid.setInUse(false);
    iteration++;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

}

void Game::resetGrid() {
    iteration = 0;
    grid.generateGrid();
}

void Game::pause() {
    setPlay(!isPlay());
}

void Game::asyncGameOfLife() {
    launched = true;
    while(launched) {
        while (play && getGrid().isGenerated()) {
            gameOfLife();
        }
    }
}

bool Game::isLaunched() const {
    return launched;
}

void Game::setLaunched(bool launched) {
    Game::launched = launched;
}

sf::Vector2i Game::mouseToCellPos(sf::Vector2i mouse) {
    return Grid::mouseToCellPos(grid, mouse);
}

void Game::changeCellStatus(sf::Vector2i position, int status) {
    grid.findCell(position).setStatus(status);
}

int Game::getCellStatus(sf::Vector2i position) {
    return grid.findCell(position).getStatus();
}

int Game::getIteration() const {
    return iteration;
}

void Game::setIteration(int iteration) {
    Game::iteration = iteration;
}
