#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h" // ��������������, ��� � ��� ���� ������������ ���� ��� ������ Game

// ������� ��� ����������� ����
int showMenu(sf::RenderWindow& window, sf::Font& font, sf::Sprite& background, sf::Sound& navigateSound);

// ������� ��� ����������� ���������� �� ����
void showInfo(sf::RenderWindow& window, sf::Font& font, sf::Sprite& background);

int main()
{
    setlocale(LC_ALL, "");
    srand(static_cast<unsigned int>(time(nullptr)));

    sf::RenderWindow window(sf::VideoMode(450, 750), "Game Menu", sf::Style::Close | sf::Style::Titlebar);

    // �����
    sf::Font font;
    if (!font.loadFromFile("res/font/font.ttf")) // �������� �� ���� � ������ ������
    {
        std::cerr << "������ �������� ������" << std::endl;
        return -1;
    }

    // ���
    sf::Texture backgroundMenuTexture;
    if (!backgroundMenuTexture.loadFromFile("res/gfx/Fon_menyu.png")) // ��� ����
    {
        std::cerr << "������ �������� ����" << std::endl;
        return -1;
    }

    sf::Sprite backgroundMenu(backgroundMenuTexture);

    sf::Texture backgroundInfoTexture;
    if (!backgroundInfoTexture.loadFromFile("res/gfx/Fon_igry.png")) // ��� ����
    {
        std::cerr << "������ �������� ����" << std::endl;
        return -1;
    }

    sf::Sprite backgroundInfo(backgroundInfoTexture);

    // �����
    sf::SoundBuffer navigateBuffer;
    if (!navigateBuffer.loadFromFile("res/sfx/minimenu.wav")) // ���� ������������
    {
        std::cerr << "������ �������� ����� ������������" << std::endl;
        return -1;
    }

    sf::Sound navigateSound;
    navigateSound.setBuffer(navigateBuffer);

    sf::SoundBuffer gameStartBuffer;
    if (!gameStartBuffer.loadFromFile("res/sfx/gamestart.wav")) // ���� ������ ����
    {
        std::cerr << "������ �������� ����� ������� ����" << std::endl;
        return -1;
    }

    sf::Sound gameStartSound;
    gameStartSound.setBuffer(gameStartBuffer);


    while (window.isOpen())
    {
        int menuChoice = showMenu(window, font, backgroundMenu, navigateSound);

        if (menuChoice == 0)
        {
            gameStartSound.play();
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

// ������� ��� ����������� ����
int showMenu(sf::RenderWindow& window, sf::Font& font, sf::Sprite& background, sf::Sound& navigateSound)
{
    sf::Text menu[3];
    std::string menuItems[3] = { "Play", "Info", "Exit" };

    for (int i = 0; i < 3; ++i)
    {
        menu[i].setFont(font);
        menu[i].setCharacterSize(40);
        menu[i].setString(menuItems[i]);
        menu[i].setPosition(200, 230 + i * 50);
    }

    int selectedItem = 0; // ��������� ��������� ������� ����

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

        // ��������� ����
        window.draw(background);

        // ��������� ����
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

    return -1; // ���� ���� �������, ���������� -1
}

// ������� ��� ����������� ���������� �� ����
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
                return; // ������������ � ����
            }
        }

        window.clear();

        // ��������� ����
        window.draw(background);

        // ��������� ������ � �����������
        window.draw(infoText);
        window.display();
    }
}