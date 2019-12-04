//
// Created by Fraxinus on 19/11/2019.
//

#ifndef GAMEOFLIFESFML_CELL_H
#define GAMEOFLIFESFML_CELL_H

#include <map>
#include "SFML/Graphics.hpp"

class Cell : public sf::Drawable {
private:
    sf::Vector2f position;
    sf::Vector2f positionIndexes;
    sf::Vector2f size;
    std::map<char, Cell&> neighbors;
    int status;
public:
    Cell(sf::Vector2f position, sf::Vector2f size, int status);
    Cell();
    sf::Vector2f getPosition();

    void setPosition(sf::Vector2f position);

    sf::Vector2f getPositionIndexes();

    void setPositionIndexes(sf::Vector2f positionIndexes);

    sf::Vector2f getSize();

    void setSize(sf::Vector2f size);

    const std::map<char, Cell &> & getNeighbors() const;

    void setNeighbors(const std::map<char, Cell&> &neighbors);

    int getStatus() const;

    void setStatus(int status);

    int numberOfNeighbors() const;
    int numberOfNeighbors(int status) const;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        sf::RectangleShape r_cell = sf::RectangleShape(size);
        r_cell.setPosition(position);
        r_cell.setOutlineThickness(-1);
        r_cell.setOutlineColor(sf::Color::Black);
        if(status == 1)
            r_cell.setFillColor(sf::Color::White);
        else
            r_cell.setFillColor(sf::Color::Black);
        target.draw(r_cell);
    }
};


#endif //GAMEOFLIFESFML_CELL_H
