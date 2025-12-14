#pragma once
#include <SFML/Graphics.hpp>

//Klasa reprezentujaca paletke
class Paddle
{
private:
    sf::RectangleShape m_shape;
    sf::Vector2f velocity;

public:
    Paddle(sf::Vector2f startPos, sf::Vector2f size, sf::Vector2f startVel);

    sf::Vector2f getPosition() const { return m_shape.getPosition(); }
    void setPosition(sf::Vector2f pos) { m_shape.setPosition(pos); }


    void ruch(sf::Time dt, sf::Vector2f windowSize);
    void draw(sf::RenderTarget& window);
    sf::FloatRect getGlobalBounds() const;
};


