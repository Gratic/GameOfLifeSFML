//
// Created by Fraxinus on 19/11/2019.
//

#ifndef GAMEOFLIFESFML_GRID_H
#define GAMEOFLIFESFML_GRID_H

#include <vector>
#include "Cell.h"
#include "SFML/Graphics.hpp"
#include "iostream"

class Grid : public sf::Drawable {
private:
    std::vector<std::vector<Cell>> cells;
    sf::Vector2f numberOfCells;
    sf::Vector2f sizeOfCell;
    sf::Vector2f position;
public:
    Grid(const sf::Vector2f &numberOfCells, const sf::Vector2f &position, const sf::Vector2f &sizeOfCell);

    std::vector<std::vector<Cell>> &getCells();

    void setCells(const std::vector<std::vector<Cell>> &cells);

    const sf::Vector2f &getNumberOfCells();

    void setNumberOfCells(const sf::Vector2f &numberOfCells);

    const sf::Vector2f &getPosition();

    void setPosition(const sf::Vector2f &position);

    const sf::Vector2f &getSizeOfCell();

    void setSizeOfCell(const sf::Vector2f &sizeOfCell);

    void generateGrid();
    void findNeighbors();
    Cell findCell(int x, int y);
    Cell findCell(sf::Vector2f position);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for(int i(0); i < numberOfCells.x; i++)
        {
            for(int j(0); j < numberOfCells.y; j++)
            {
                target.draw(cells[i][j]);
            }
        }
    }
};


#endif //GAMEOFLIFESFML_GRID_H
