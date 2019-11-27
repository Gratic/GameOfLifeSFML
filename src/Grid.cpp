//
// Created by Fraxinus on 19/11/2019.
//

#include "Grid.h"
#include <vector>
#include "Cell.h"
#include "SFML/Graphics.hpp"
#include "iostream"

std::vector<std::vector<Cell>> &Grid::getCells() {
    return cells;
}

void Grid::setCells(const std::vector<std::vector<Cell>> &cells) {
    Grid::cells = cells;
}

const sf::Vector2f &Grid::getNumberOfCells() {
    return numberOfCells;
}

void Grid::setNumberOfCells(const sf::Vector2f &numberOfCells) {
    Grid::numberOfCells = numberOfCells;
}

const sf::Vector2f &Grid::getPosition() {
    return position;
}

void Grid::setPosition(const sf::Vector2f &position) {
    Grid::position = position;
}

Grid::Grid(const sf::Vector2f &numberOfCells, const sf::Vector2f &position, const sf::Vector2f &sizeOfCell) : numberOfCells(numberOfCells),
                                                                              position(position),sizeOfCell(sizeOfCell){
    cells = std::vector<std::vector<Cell>>(numberOfCells.x, std::vector<Cell>(numberOfCells.y));
}

const sf::Vector2f &Grid::getSizeOfCell() {
    return sizeOfCell;
}

void Grid::setSizeOfCell(const sf::Vector2f &sizeOfCell) {
    Grid::sizeOfCell = sizeOfCell;
}

void Grid::generateGrid() {
    for(int i(0); i < numberOfCells.x; i++)
    {
        cells[i] = std::vector<Cell>();
        for(int j(0); j < numberOfCells.y; j++)
        {
            sf::Vector2f position = sf::Vector2f(i * sizeOfCell.x, j * sizeOfCell.y);
            Cell c = Cell(position, sizeOfCell, 0);
            cells[i].push_back(c);
        }
    }
}

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

Cell Grid::findCell(int x, int y)
{
    for(int i(0); i < i < numberOfCells.x; i++) {
        for(int j(0); j < numberOfCells.y; j++) {
            if (cells[i][j].getPositionIndexes().x == x && cells[i][j].getPositionIndexes().y == y)
                return cells[i][j];
        }
    }
}

Cell Grid::findCell(sf::Vector2f position) {
    for(int i(0); i < cells.size(); i++) {
        for(int j(0); j < numberOfCells.y; j++) {
            if(cells[i][j].getPositionIndexes().x == position.x && cells[i][j].getPositionIndexes().y == position.y)
                return cells[i][j];
        }
    }
}