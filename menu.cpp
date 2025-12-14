#include "menu.h"

// Konstruktor klasy Menu – inicjalizuje czcionkê, opcje menu i ich pozycje
Menu::Menu(float width, float height)
{
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "B³¹d: nie mo¿na wczytaæ czcionki arial.ttf w menu!\n";
    }

    selectedIndex = 0;

    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
    {
        menu[i].setFont(font);
        menu[i].setCharacterSize(35);
        menu[i].setFillColor(sf::Color::White);
    }

    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Nowa gra");
    menu[0].setPosition(sf::Vector2f(width / 2.f - 100, height / 3.f));

    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Wczytaj gre");
    menu[1].setPosition(width / 2.f - 100, height / 3.f + 80);

    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Wyjscie");
    menu[2].setPosition(sf::Vector2f(width / 2.f - 100, height / 3.f + 160));

    menu[3].setFillColor(sf::Color::White);
    menu[3].setString("Instrukcja sterowania");
    menu[3].setPosition(width / 2.f - 100, height / 3.f + 240);
}

// Rysowanie menu na oknie
void Menu::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
        window.draw(menu[i]);
}

// Przesuwanie zaznaczenia w górê
void Menu::MoveUp()
{
    if (selectedIndex > 0)
    {
        menu[selectedIndex].setFillColor(sf::Color::White);
        selectedIndex--;
        menu[selectedIndex].setFillColor(sf::Color::Red);
    }
}

// Przesuwanie zaznaczenia w dó³
void Menu::MoveDown()
{
    if (selectedIndex < MAX_NUMBER_OF_ITEMS - 1)
    {
        menu[selectedIndex].setFillColor(sf::Color::White);
        selectedIndex++;
        menu[selectedIndex].setFillColor(sf::Color::Red);
    }
}
