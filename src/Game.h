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
    sf::Vector2i position;
    sf::Vector2i numberOfCells;
    sf::Vector2i sizeOfCells;
    bool play;
    bool launched;
    int iteration;
    int delay;
public:
    Game(const sf::Vector2i &position, const sf::Vector2i &numberOfCells, const sf::Vector2i &sizeOfCells, bool play, int delay);

    Game();

    void resetGrid();

    void pause();

    void gameOfLife();

    void asyncGameOfLife();

    sf::Vector2i mouseToCellPos(sf::Vector2i mouse);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(grid);
    }


    Grid & getGrid();

    void setGrid(const Grid &grid);

    const sf::Vector2i &getPosition();

    void setPosition(const sf::Vector2i &position);

    const sf::Vector2i &getNumberOfCells();

    void setNumberOfCells(const sf::Vector2i &numberOfCells);

    const sf::Vector2i &getSizeOfCells();

    void setSizeOfCells(const sf::Vector2i &sizeOfCells);

    bool isPlay();

    void setPlay(bool play);

    bool isLaunched() const;

    void setLaunched(bool launched);

    int getIteration() const;

    void setIteration(int iteration);

    void setCellStatus(sf::Vector2i position, int status);

    int getCellStatus(sf::Vector2i position);

    int getDelay() const;

    void setDelay(int delay);
};


#endif //GAMEOFLIFESFML_GAME_H
