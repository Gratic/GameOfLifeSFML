//
// Created by Fraxinus on 19/11/2019.
//

#include "Grid.h"
#include "Cell.h"
#include "SFML/Graphics.hpp"
#include <vector>

std::vector<std::vector<Cell>> &Grid::getCells() {
    return cells;
}

void Grid::setCells(const std::vector<std::vector<Cell>> &cells) {
    Grid::cells = cells;
}

const sf::Vector2i &Grid::getNumberOfCells() {
    return numberOfCells;
}

void Grid::setNumberOfCells(const sf::Vector2i &numberOfCells) {
    Grid::numberOfCells = numberOfCells;
}

const sf::Vector2i &Grid::getPosition() {
    return position;
}

void Grid::setPosition(const sf::Vector2i &position) {
    Grid::position = position;
}

Grid::Grid(const sf::Vector2i &numberOfCells, const sf::Vector2i &position, const sf::Vector2i &sizeOfCell) : numberOfCells(numberOfCells),
                                                                              position(position),sizeOfCell(sizeOfCell),
                                                                              generated(false), inUse(false){
    cells = std::vector<std::vector<Cell>>(numberOfCells.x, std::vector<Cell>(numberOfCells.y));
}

const sf::Vector2i &Grid::getSizeOfCell() {
    return sizeOfCell;
}

void Grid::setSizeOfCell(const sf::Vector2i &sizeOfCell) {
    Grid::sizeOfCell = sizeOfCell;
}

void Grid::generateGrid() {
    resetGrid();

    for(int i(0); i < numberOfCells.x; i++)
    {
        cells[i] = std::vector<Cell>();
        for(int j(0); j < numberOfCells.y; j++)
        {
            sf::Vector2i position = sf::Vector2i(i * sizeOfCell.x, j * sizeOfCell.y);
            Cell c = Cell(position, sizeOfCell, 0);
            cells[i].push_back(c);
        }
    }

    findNeighbors();
    generated = true;
}

void Grid::resetGrid() {
    generated = false;

    while(inUse)
    {

    }
    cells = std::vector<std::vector<Cell>>(numberOfCells.x, std::vector<Cell>(numberOfCells.y));
}

/*
 * findNeighbors() : for each cell, give her their neighbors
 */
void Grid::findNeighbors() {
    for(int i(0); i < numberOfCells.x; i++)
    {
        for(int j(0); j < numberOfCells.y; j++) {
            std::map<char, Cell&> map;
            for (int x(-1); x <= 1; x++) {
                for (int y(-1); y <= 1; y++) {
                    if (i + x >= 0 && i + x < numberOfCells.x && j + y >= 0 && j + y < numberOfCells.y) {
                        if (x == -1) {
                            if (y == -1)
                                map.insert(std::pair<char, Cell&>('a', cells[i + x][j + y]));
                            else if (y == 0)
                                map.insert(std::pair<char, Cell&>('q', cells[i + x][j + y]));
                            else if (y == 1)
                                map.insert(std::pair<char, Cell&>('w', cells[i + x][j + y]));

                        } else if (x == 0) {
                            if (y == -1)
                                map.insert(std::pair<char, Cell&>('z', cells[i + x][j + y]));
                            else if (y == 1)
                                map.insert(std::pair<char, Cell&>('x', cells[i + x][j + y]));

                        } else if (x == 1) {
                            if (y == -1)
                                map.insert(std::pair<char, Cell&>('e', cells[i + x][j + y]));
                            else if (y == 0)
                                map.insert(std::pair<char, Cell&>('d', cells[i + x][j + y]));
                            else if (y == 1)
                                map.insert(std::pair<char, Cell&>('c', cells[i + x][j + y]));
                        }

                    }
                }
            }
            cells[i][j].setNeighbors(map);
        }
    }
}

Cell& Grid::findCell(int x, int y)
{
    for(int i(0); i < i < numberOfCells.x; i++) {
        for(int j(0); j < numberOfCells.y; j++) {
            if (cells[i][j].getPositionIndexes().x == x && cells[i][j].getPositionIndexes().y == y)
                return cells[i][j];
        }
    }
}

Cell& Grid::findCell(sf::Vector2f position) {
    return findCell(position.x, position.y);
}

Cell& Grid::findCell(sf::Vector2i position) {
    return findCell(position.x, position.y);
}

bool Grid::isGenerated() const {
    return generated;
}

void Grid::setGenerated(bool generated) {
    Grid::generated = generated;
}

bool Grid::isInUse() const {
    return inUse;
}

void Grid::setInUse(bool inUse) {
    Grid::inUse = inUse;
}

sf::Vector2i Grid::mouseToCellPos(Grid grid, sf::Vector2i mouse) {
    sf::Vector2i cellpos;

    for(int x(0); x < grid.numberOfCells.x; x++)
    {
        for(int y(0); y < grid.numberOfCells.y; y++)
        {
            if(Grid::pointInRect(mouse.x,
                    mouse.y,
                    grid.cells[x][y].getPosition().x,
                    grid.cells[x][y].getPosition().y,
                    grid.sizeOfCell.x,
                    grid.sizeOfCell.y))
            {
                cellpos = sf::Vector2i(x, y);
                break;
            }
        }
    }

    return cellpos;
}


bool Grid::pointInRect(float px, float py, float rx, float ry, float rw, float rh) {

    // is the point inside the rectangle's bounds?
    return px >= rx &&        // right of the left edge AND
           px <= rx + rw &&   // left of the right edge AND
           py >= ry &&        // below the top AND
           py <= ry + rh;
}
