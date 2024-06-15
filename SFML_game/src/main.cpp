#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"

int main()
{
    setlocale(LC_ALL, "");
    srand(static_cast<unsigned int>(time(nullptr)));

    Game game;
    game.run();

    return 0;
}