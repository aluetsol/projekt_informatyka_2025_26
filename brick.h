#pragma once
#include <SFML/Graphics.hpp>
#include <array>

//Klasa reprezentujaca pojedynczy klocek z punktacj¹ i ¿yciem
class Brick : public sf::RectangleShape
{
private:
    int life;
    bool destroyed;
    static const std::array<sf::Color, 4> LUT;

public:
    Brick(sf::Vector2f pos, sf::Vector2f size, int hp);
    void trafienie();
    bool czyZniszczony() const;
    void draw(sf::RenderTarget& window);

    int getHP() const { return life; }
};

