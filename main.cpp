#include "SFML/Graphics.hpp"
#include <iostream>
#include "src/Grid.h"
#include "src/Cell.h"
#include "src/Game.h"
#include <thread>
#include <chrono>

int WINDOW_WIDTH = 500;
int WINDOW_HEIGHT = 500;
int SIZE_CELL = 10;
int NUMBER_OF_CELLS = 10;

int main() {
    Game gol(sf::Vector2f(0,0), sf::Vector2f(NUMBER_OF_CELLS, NUMBER_OF_CELLS),sf::Vector2f(SIZE_CELL, SIZE_CELL), true);

//    std::thread th = std::thread(&Game::gameOfLife, &gol);

//    gol.getGrid().getCells()[0][1].setStatus(1);
//    gol.getGrid().getCells()[1][1].setStatus(1);
//    gol.getGrid().getCells()[2][1].setStatus(1);

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game Of Life | Zaleks");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        gol.gameOfLife();
        window.clear();
        window.draw(gol);
        window.display();
    }

    return 0;
}