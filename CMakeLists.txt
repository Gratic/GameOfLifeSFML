cmake_minimum_required(VERSION 3.1)

project(GameOfLifeSFML)

## If you want to link SFML statically
set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "C:/Libraries/SFML/lib/cmake/SFML")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -pthread" )

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
add_executable(GameOfLifeSFML main.cpp src/Cell.cpp src/Cell.h src/Grid.cpp src/Grid.h src/Game.cpp src/Game.h)
target_link_libraries(GameOfLifeSFML sfml-graphics)