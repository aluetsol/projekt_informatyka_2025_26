#include "rules.h"
#include <iostream>

// Konstruktor klasy ControlsWindow – inicjalizuje czcionkê i tekst instrukcji
ControlsWindow::ControlsWindow()
{
    if (!font.loadFromFile("arial.ttf"))
        std::cout << "Blad wczytywania czcionki\n";

    text.setFont(font);
    text.setCharacterSize(26);
    text.setFillColor(sf::Color::White);
    text.setString(
        "Instrukcja sterowania:\n\n"
        "A - ruch w lewo\n"
        "D - ruch w prawo\n"
        "F5 - zapis gry\n"
        "ENTER - zatwierdzenie opcji\n"
        "ESC - powrot\n"
    );
    text.setPosition(40, 40);
}

// Wyœwietlanie okna z instrukcj¹ sterowania
void ControlsWindow::show()
{
    sf::RenderWindow win(sf::VideoMode(600, 400), "Instrukcja sterowania");

    while (win.isOpen())
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed
                || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                win.close();
        }

        win.clear(sf::Color(20, 20, 20));
        win.draw(text);
        win.display();
    }
}
