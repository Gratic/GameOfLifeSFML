#include "SFML/Graphics.hpp"
#include <iostream>
#include "src/Grid.h"
#include "src/Cell.h"
#include "src/Game.h"
#include <thread>
#include <chrono>

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;
const int SIZE_CELL = 10;
const int NUMBER_OF_CELLS_X = 100;
const int NUMBER_OF_CELLS_Y = 80;
const char GENERATION_MODE = 'M';
const int MIN_DELAY_ITERATION = 10;

int main() {
    Game gol(sf::Vector2f(0,0), sf::Vector2f(NUMBER_OF_CELLS_X, NUMBER_OF_CELLS_Y),sf::Vector2f(SIZE_CELL, SIZE_CELL), false, MIN_DELAY_ITERATION);

    // Size and number of cells determined by GENERATION_MODE const
    // TODO: changeable GENERATION_MODE
    if(GENERATION_MODE == 'A')
    {
        // Size known, fill the full width and height
        gol.setNumberOfCells(sf::Vector2f(WINDOW_WIDTH/SIZE_CELL, WINDOW_HEIGHT/SIZE_CELL));
    }
    else if (GENERATION_MODE == 'M')
    {
        // Number of cells known, fill the full width and height
        gol.setSizeOfCells(sf::Vector2f(WINDOW_WIDTH/NUMBER_OF_CELLS_X, WINDOW_HEIGHT/NUMBER_OF_CELLS_Y));
    }


    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game Of Life | Zaleks");

    // Launch of the parallel thread
    std::thread th = std::thread(&Game::asyncGameOfLife, &gol);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if(event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::P) {
                    gol.pause();
                }
                else if (event.key.code == sf::Keyboard::R) {
                    gol.resetGrid();
                }
            }
            if(event.type == sf::Event::MouseButtonReleased)
            {
                // The clicked cell is toggled between 1 and 0
                sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                sf::Vector2i cellPos = gol.mouseToCellPos(localPosition);
                gol.setCellStatus(cellPos, (gol.getCellStatus(cellPos) + 1) % 2);
            }
        }

        window.clear();     // Clean
        window.draw(gol);   // Draw
        window.display();   // Display
    }
    gol.setLaunched(false); // End the game of life thread

    return 0;
}