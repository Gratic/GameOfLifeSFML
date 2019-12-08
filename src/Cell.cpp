//
// Created by Fraxinus on 19/11/2019.
//

#include "Cell.h"
#include <map>
#include "SFML/Graphics.hpp"

Cell::Cell(sf::Vector2i position, sf::Vector2i size, int status) : position(position), size(size), status(rand() % 2) {
    setNeighbors(std::map<char,Cell&>());
    positionIndexes = sf::Vector2i(position.x / size.x, position.y / size.x);
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

sf::Vector2i Cell::getPosition() {
    return position;
}

void Cell::setPosition(sf::Vector2i position) {
    Cell::position = position;
}

sf::Vector2i Cell::getPositionIndexes() {
    return positionIndexes;
}

void Cell::setPositionIndexes(sf::Vector2i positionIndexes) {
    Cell::positionIndexes = positionIndexes;
}

sf::Vector2i Cell::getSize() {
    return size;
}

void Cell::setSize(sf::Vector2i size) {
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
