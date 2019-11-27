//
// Created by Fraxinus on 19/11/2019.
//

#include "Cell.h"
#include <map>
#include "SFML/Graphics.hpp"
#include <iostream>
#include <random>

sf::Vector2f Cell::getPosition() {
    return position;
}

void Cell::setPosition(sf::Vector2f position) {
    Cell::position = position;
}

sf::Vector2f Cell::getPositionIndexes() {
    return positionIndexes;
}

void Cell::setPositionIndexes(sf::Vector2f positionIndexes) {
    Cell::positionIndexes = positionIndexes;
}

sf::Vector2f Cell::getSize() {
    return size;
}

void Cell::setSize(sf::Vector2f size) {
    Cell::size = size;
}

const std::map<char, Cell &> & Cell::getNeighbors() const {
    return neighbors;
}

void Cell::setNeighbors(const std::map<char, Cell&> &neighbors) {
    Cell::neighbors = neighbors;
}

int Cell::getStatus() const {
    return status;
}

void Cell::setStatus(int status) {
    Cell::status = status;
}

Cell::Cell(sf::Vector2f position, sf::Vector2f size, int status) : position(position), size(size), status(rand() % 2) {
    setNeighbors(std::map<char,Cell&>());
    positionIndexes = sf::Vector2f(position.x / size.x, position.y / size.x);
}

Cell::Cell() {}

int Cell::numberOfNeighbors() const {
    return neighbors.size();
}

int Cell::numberOfNeighbors(int status) const {
    int count(0);
    for (auto const& x : getNeighbors()) {
        if(x.second.getStatus() == status)
            count++;
    }
    return count;
}
