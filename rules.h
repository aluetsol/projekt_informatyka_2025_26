#pragma once
#include <SFML/Graphics.hpp>

// Klasa ControlsWindow – wyœwietla okno z instrukcj¹ sterowania
class ControlsWindow
{
private:
    sf::Font font;
    sf::Text text;

public:
    ControlsWindow();

    void show();
};