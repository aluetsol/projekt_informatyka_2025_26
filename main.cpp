#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "menu.h"
#include "game.h"
#include "GameState.h"
#include "rules.h"

// Definicja stanów gry
enum class GameStateFlag { Menu, Playing, Controls, Exiting };

// Główna pętla gry
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Arkanoid");
    window.setFramerateLimit(60);

    Menu menu(window.getSize().x, window.getSize().y);

    std::unique_ptr<Game> game = std::make_unique<Game>();
    GameState saveState;

    GameStateFlag currentState = GameStateFlag::Menu;
    sf::Clock deltaClock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (currentState == GameStateFlag::Menu && event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                    menu.MoveUp();
                else if (event.key.code == sf::Keyboard::Down)
                    menu.MoveDown();
                else if (event.key.code == sf::Keyboard::Enter)
                {
                    int choice = menu.getSelectedItem();

                    if (choice == 0)
                    {
                        game = std::make_unique<Game>();
                        currentState = GameStateFlag::Playing;
                    }
                    else if (choice == 1)
                    {
                        if (saveState.loadFromFile("save.txt"))
                        {
                            saveState.apply(game->getPaddle(), game->getBall(), game->getBlocks(), game->getBlockSize());
                            game->setScore(saveState.getSavedScore());
                            currentState = GameStateFlag::Playing;
                        }
                        else
                        {
                            std::cout << "Brak pliku save.txt!\n";
                        }
                    }
                    else if (choice == 2)
                    {
                        window.close();
                    }
                    else if (choice == 3)
                    {
                        ControlsWindow ctrl;
                        ctrl.show();
                    }
                }
            }

            if (currentState == GameStateFlag::Playing && event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::F5)
                {
                    saveState.capture(game->getPaddle(), game->getBall(), game->getBlocks(), game->getScore());
                    if (saveState.saveToFile("save.txt"))
                        std::cout << "Gra zapisana!\n";
                    else
                        std::cout << "Blad zapisu!\n";
                }
            }
        }

        sf::Time dt = deltaClock.restart();

        if (currentState == GameStateFlag::Playing)
        {
            game->update(dt, window.getSize());
        }

        window.clear();

        if (currentState == GameStateFlag::Menu)
        {
            menu.draw(window);
        }
        else if (currentState == GameStateFlag::Playing)
        {
            game->render(window);

            if (game->isGameOver())
            {
                if (game->isFontLoaded())
                {
                    sf::Text t;
                    t.setFont(game->getFont());
                    t.setString("GAME OVER");
                    t.setCharacterSize(60);
                    t.setFillColor(sf::Color::Red);
                    t.setPosition(200.f, 250.f);
                    window.draw(t);
                    window.display();
                    sf::sleep(sf::seconds(2));
                }
                else
                {
                    std::cout << "GAME OVER (font not loaded)\n";
                    sf::sleep(sf::seconds(2));
                }

                currentState = GameStateFlag::Menu;
                continue;
            }

            if (game->isWin())
            {
                if (game->isFontLoaded())
                {
                    sf::Text t;
                    t.setFont(game->getFont());
                    t.setString("YOU WIN!");
                    t.setCharacterSize(60);
                    t.setFillColor(sf::Color::Green);
                    t.setPosition(230.f, 250.f);
                    window.draw(t);
                    window.display();
                    sf::sleep(sf::seconds(2));
                }
                else
                {
                    std::cout << "YOU WIN! (font not loaded)\n";
                    sf::sleep(sf::seconds(2));
                }

                currentState = GameStateFlag::Menu;
                continue;
            }
        }

        window.display();
    }

    return 0;
}
