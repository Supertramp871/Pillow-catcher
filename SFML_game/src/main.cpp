#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h" 

// Function for displaying menu
int showMenu(sf::RenderWindow& window, sf::Font& font, sf::Sprite& background, sf::Sound& navigateSound);

// Function to display game information
void showInfo(sf::RenderWindow& window, sf::Font& font, sf::Sprite& background);

int main()
{
    setlocale(LC_ALL, "");
    srand(static_cast<unsigned int>(time(nullptr)));

    sf::RenderWindow window(sf::VideoMode(450, 750), "Game Menu", sf::Style::Close | sf::Style::Titlebar);

    // Text
    sf::Font font;
    if (!font.loadFromFile("res/font/font.ttf"))
    {
        std::cerr << "Font loading error" << std::endl;
        return -1;
    }

    // Фон
    sf::Texture backgroundMenuTexture;
    if (!backgroundMenuTexture.loadFromFile("res/gfx/Fon_menyu.png")) // menu background
    {
        std::cerr << "Ошибка загрузки фона" << std::endl;
        return -1;
    }

    sf::Sprite backgroundMenu(backgroundMenuTexture);

    sf::Texture backgroundInfoTexture;
    if (!backgroundInfoTexture.loadFromFile("res/gfx/Fon_igry.png")) // game background
    {
        std::cerr << "Error loading background" << std::endl;
        return -1;
    }

    sf::Sprite backgroundInfo(backgroundInfoTexture);

    // Аудио
    sf::SoundBuffer navigateBuffer;
    if (!navigateBuffer.loadFromFile("res/sfx/minimenu.wav")) // switching sound
    {
        std::cerr << "Error loading switching sound" << std::endl;
        return -1;
    }

    sf::Sound navigateSound;
    navigateSound.setBuffer(navigateBuffer);

    while (window.isOpen())
    {
        int menuChoice = showMenu(window, font, backgroundMenu, navigateSound);

        if (menuChoice == 0)
        {
            Game game;
            game.run();
        }
        else if (menuChoice == 1)
        {
            showInfo(window, font, backgroundInfo);
        }
        else if (menuChoice == 2)
        {
            window.close();
        }
    }

    return 0;
}

// Function for displaying menu
int showMenu(sf::RenderWindow& window, sf::Font& font, sf::Sprite& background, sf::Sound& navigateSound)
{
    sf::Text menu[3];
    std::string menuItems[3] = { "Play", "Info", "Exit" };
    window.setMouseCursorVisible(false);

    for (int i = 0; i < 3; ++i)
    {
        menu[i].setFont(font);
        menu[i].setCharacterSize(40);
        menu[i].setString(menuItems[i]);
        menu[i].setPosition(200.f, 230.f + i * 50.f);
    }

    int selectedItem = 0; // Initial selected menu item

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    selectedItem = (selectedItem - 1 + 3) % 3;
                    navigateSound.play();
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    selectedItem = (selectedItem + 1) % 3;
                    navigateSound.play();
                }
                else if (event.key.code == sf::Keyboard::Enter)
                {
                    return selectedItem;
                }
            }
        }

        window.clear();

        // Background rendering
        window.draw(background);

        // Menu rendering
        for (int i = 0; i < 3; ++i)
        {
            if (i == selectedItem)
                menu[i].setFillColor(sf::Color::Red);
            else
                menu[i].setFillColor(sf::Color::White);

            window.draw(menu[i]);
        }

        window.display();
    }

    return -1;
}

// Function to display game information
void showInfo(sf::RenderWindow& window, sf::Font& font, sf::Sprite& background)
{
    sf::Text infoText;
    infoText.setFont(font);
    infoText.setCharacterSize(28);
    infoText.setFillColor(sf::Color::White);
    infoText.setString("Author: Yushin Alexander O738B. \n\nCatch all the notes and emoticons.\n\nPress Left - to move left.\n\nPress Right - to move right.\n\nPress any key to return to the menu.");
    infoText.setPosition(40, 50);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                return; // Returning to the menu
            }
        }

        window.clear();

        // Background rendering
        window.draw(background);

        // Rendering text with information
        window.draw(infoText);
        window.display();
    }
}