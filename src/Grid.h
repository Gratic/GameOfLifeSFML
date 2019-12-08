//
// Created by Fraxinus on 19/11/2019.
//

#ifndef GAMEOFLIFESFML_GRID_H
#define GAMEOFLIFESFML_GRID_H

#include "Cell.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include "iostream"

class Grid : public sf::Drawable {
private:
    std::vector<std::vector<Cell>> cells;
    sf::Vector2i numberOfCells;
    sf::Vector2i sizeOfCell;
    sf::Vector2i position;
    bool generated;
    bool inUse;
public:
    Grid(const sf::Vector2i &numberOfCells, const sf::Vector2i &position, const sf::Vector2i &sizeOfCell);

    void generateGrid();
    void findNeighbors();

    Cell& findCell(int x, int y);
    Cell& findCell(sf::Vector2f position);
    Cell& findCell(sf::Vector2i position);

    void resetGrid();

    static sf::Vector2i mouseToCellPos(Grid grid, sf::Vector2i mouse);

    static bool pointInRect(float px, float py, float rx, float ry, float rw, float rh);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if(generated) {
            for (int i(0); i < numberOfCells.x; i++) {
                for (int j(0); j < numberOfCells.y; j++) {
                    target.draw(cells[i][j]);
                }
            }
        }
    }

    std::vector<std::vector<Cell>> &getCells();

    void setCells(const std::vector<std::vector<Cell>> &cells);

    const sf::Vector2i &getNumberOfCells();

    void setNumberOfCells(const sf::Vector2i &numberOfCells);

    const sf::Vector2i &getPosition();

    void setPosition(const sf::Vector2i &position);

    const sf::Vector2i &getSizeOfCell();

    void setSizeOfCell(const sf::Vector2i &sizeOfCell);

    bool isGenerated() const;

    void setGenerated(bool generated);

    bool isInUse() const;

    void setInUse(bool inUse);
};


#endif //GAMEOFLIFESFML_GRID_H
