#include "paddle.h"

// Konstruktor paletki inicjalizuj¹cy pozycjê, kolor i rozmiar
Paddle::Paddle(sf::Vector2f startPos, sf::Vector2f size, sf::Vector2f startVel)
{
    velocity = startVel;
    m_shape.setPosition(startPos);
    m_shape.setSize(size);
    m_shape.setFillColor(sf::Color::Cyan);
    m_shape.setOrigin(size.x / 2.f, size.y / 2.f);
}

// Aktualizacja ruchu paletki na podstawie wejœcia klawiatury i ograniczeñ okna
void Paddle::ruch(sf::Time dt, sf::Vector2f windowSize)
{
    float dx = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        dx -= velocity.x * dt.asSeconds();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        dx += velocity.x * dt.asSeconds();

    sf::Vector2f pos = m_shape.getPosition();
    pos.x += dx;

    float half = m_shape.getSize().x / 2.f;

    if (pos.x - half < 0)
        pos.x = half;
    if (pos.x + half > windowSize.x)
        pos.x = windowSize.x - half;

    m_shape.setPosition(pos);
}

// Rysowanie paletki na ekranie
void Paddle::draw(sf::RenderTarget& window)
{
    window.draw(m_shape);
}

// Pobranie globalnych granic paletki (do wykrywania kolizji)
sf::FloatRect Paddle::getGlobalBounds() const
{
    return m_shape.getGlobalBounds();
}



