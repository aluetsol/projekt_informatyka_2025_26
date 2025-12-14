#include "ball.h"

// Konstruktor inicjalizuj¹cy pozycjê, promieñ, kolor i prêdkoœæ pi³ki
Ball::Ball(sf::Vector2f startPos, float radius, sf::Vector2f startVel)
{
    velocity = startVel;
    m_shape.setPosition(startPos);
    m_shape.setRadius(radius);
	m_shape.setOrigin(radius, radius); // Ustawienie œrodka jako punktu odniesienia
    m_shape.setFillColor(sf::Color::Green);
}

// Rysowanie pi³ki na ekranie 
void Ball::draw(sf::RenderTarget& window)
{
    window.draw(m_shape);
}


// Pobranie globalnych granic pi³ki (do wykrywania kolizji)
sf::FloatRect Ball::getGlobalBounds() const
{
    return m_shape.getGlobalBounds();
}

// Aktualizacja ruchu pi³ki: odbicia od œcian, kolizja z paletk¹
void Ball::ruch(sf::Time dt, sf::Vector2f win, Paddle& pdl)
{
    m_shape.move(velocity * dt.asSeconds());

    float x = m_shape.getPosition().x;
    float y = m_shape.getPosition().y;
    float r = m_shape.getRadius();

    if (x - r < 0)
    {
        m_shape.setPosition(r, y);
        velocity.x = -velocity.x;
    }
    else if (x + r > win.x)
    {
        m_shape.setPosition(win.x - r, y);
        velocity.x = -velocity.x;
    }

    if (y - r < 0)
    {
        m_shape.setPosition(x, r);
        velocity.y = -velocity.y;
    }

    if (m_shape.getGlobalBounds().intersects(pdl.getGlobalBounds()))
    {
        velocity.y = -velocity.y;
    }

    if (y + r > win.y)
    {
        return;
    }
}

