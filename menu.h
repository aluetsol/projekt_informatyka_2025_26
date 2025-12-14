#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#define MAX_NUMBER_OF_ITEMS 4  

// Klasa Menu – zarz¹dza wyœwietlaniem i nawigacj¹ w menu g³ównym gry
class Menu
{
private:
    int selectedIndex;
    sf::Font font;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];

public:
    Menu(float width, float height);
    void draw(sf::RenderWindow& window);
    void MoveUp();
    void MoveDown();
    int getSelectedItem() const { return selectedIndex; }
};

