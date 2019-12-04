//
// Created by Fraxinus on 19/11/2019.
//

#ifndef GAMEOFLIFESFML_GAME_H
#define GAMEOFLIFESFML_GAME_H

#include <chrono>
#include <thread>
#include "SFML/Graphics.hpp"
#include "Grid.h"
#include "Cell.h"
#include "vector"

class Game : public sf::Drawable {
private:
    Grid grid;
    sf::Vector2f position;
    sf::Vector2f numberOfCells;
    sf::Vector2f sizeOfCells;
    bool play;
    bool launched;
    int iteration;
public:
    Game(const sf::Vector2f &position, const sf::Vector2f &numberOfCells, const sf::Vector2f &sizeOfCells, bool play);

    Grid & getGrid();

    void setGrid(const Grid &grid);

    const sf::Vector2f &getPosition();

    void setPosition(const sf::Vector2f &position);

    const sf::Vector2f &getNumberOfCells();

    void setNumberOfCells(const sf::Vector2f &numberOfCells);

    const sf::Vector2f &getSizeOfCells();

    void setSizeOfCells(const sf::Vector2f &sizeOfCells);

    bool isPlay();

    void setPlay(bool play);

    bool isLaunched() const;

    void setLaunched(bool launched);

    int getIteration() const;

    void setIteration(int iteration);

    void resetGrid();

    void pause();

    void gameOfLife();

    void asyncGameOfLife();

    void changeCellStatus(sf::Vector2i position, int status);

    int getCellStatus(sf::Vector2i position);

    sf::Vector2i mouseToCellPos(sf::Vector2i mouse);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(grid);
    }
};


#endif //GAMEOFLIFESFML_GAME_H
