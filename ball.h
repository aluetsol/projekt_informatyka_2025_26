#pragma once
#include <SFML/Graphics.hpp>
#include "paddle.h"

//Klasa reprezentujaca pilke
//Odpowiada za jej pozycjê, ruch, kolizje oraz zmianê kierunku
class Ball
{
private:
	sf::CircleShape m_shape; // Kszta³t reprezentuj¹cy pi³kê
	sf::Vector2f velocity;  // Prêdkoœæ pi³ki

public:
	// Konstruktor inicjalizuj¹cy pozycjê, promieñ i prêdkoœæ pi³ki
    Ball(sf::Vector2f startPos, float radius, sf::Vector2f startVel);

    //Aktualizacja ruchu pi³ki: odbicia od œcian, kolizja z paletk¹
    void ruch(sf::Time dt, sf::Vector2f win, Paddle& pdl);

	// Rysowanie pi³ki na ekranie
    void draw(sf::RenderTarget& window);

	// Odbicie pi³ki w osi X
    void odbijY() { velocity.y = -velocity.y; }

	// Pobranie globalnych granic pi³ki (do wykrywania kolizji)
    sf::FloatRect getGlobalBounds() const;

	// Pobranie pozycji i prêdkoœci pi³ki   
    sf::Vector2f getPosition() const { return m_shape.getPosition(); }
    sf::Vector2f getVelocity() const { return velocity; }

	// Ustawienie pozycji i prêdkoœci pi³ki
    void setState(sf::Vector2f newPos, sf::Vector2f newVel)
    {
        m_shape.setPosition(newPos);
        velocity = newVel;
    }
};

