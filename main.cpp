#include "SFML/Graphics.hpp"
#include <iostream>
#include "src/Grid.h"
#include "src/Cell.h"
#include "src/Game.h"
#include <thread>
#include <chrono>

// Windows and Grid Variables
int WINDOW_WIDTH = 1200;
int WINDOW_HEIGHT = 800;
int GRID_WIDTH = 1000;
int GRID_HEIGHT = 800;

// Grid and Cell Const
int SIZE_CELL = 10;
int NUMBER_OF_CELLS_X = 160;
int NUMBER_OF_CELLS_Y = 200;
char GENERATION_MODE = 'M';
int MIN_DELAY_ITERATION = 100;

int main() {
    Game gol(sf::Vector2i(0,0), sf::Vector2i(NUMBER_OF_CELLS_X, NUMBER_OF_CELLS_Y),sf::Vector2i(SIZE_CELL, SIZE_CELL), false, MIN_DELAY_ITERATION);

    sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Game Of Life | Zaleks", sf::Style::Fullscreen);
    WINDOW_WIDTH = window.getView().getSize().x;
    WINDOW_HEIGHT = window.getView().getSize().y;

    GRID_HEIGHT = WINDOW_HEIGHT;

    // Size and number of cells determined by GENERATION_MODE const
    // TODO: changeable GENERATION_MODE
    if(GENERATION_MODE == 'A')
    {
        // Size known, fill the full width and height
        gol.setNumberOfCells(sf::Vector2i(GRID_WIDTH/SIZE_CELL, GRID_HEIGHT/SIZE_CELL));
    }
    else if (GENERATION_MODE == 'M')
    {
        // Number of cells known, fill the full width and height
//        gol.setSizeOfCells(sf::Vector2i(GRID_WIDTH/NUMBER_OF_CELLS_X, GRID_HEIGHT/NUMBER_OF_CELLS_Y));
        gol.setSizeOfCells(sf::Vector2i(GRID_WIDTH/NUMBER_OF_CELLS_X, 5));
    }

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
                else if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }
            if(event.type == sf::Event::MouseButtonReleased)
            {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    // The clicked cell is toggled between 1 and 0
                    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                    sf::Vector2i cellPos = gol.mouseToCellPos(localPosition);
                    gol.setCellStatus(cellPos, (gol.getCellStatus(cellPos) + 1) % 2);
                }
            }
        }

        window.clear();     // Clean
        window.draw(gol);   // Draw
        window.display();   // Display
    }
    gol.setLaunched(false); // End the game of life thread

    return 0;
}