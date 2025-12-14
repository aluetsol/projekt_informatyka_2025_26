#include "brick.h"

const std::array<sf::Color, 4> Brick::LUT =
{
    sf::Color::Transparent,
    sf::Color(70, 0, 120),
    sf::Color(140, 0, 200),
    sf::Color(200, 80, 255)
};

// Konstruktor klocka inicjalizuj¹cy pozycjê, rozmiar i liczbê ¿yæ
Brick::Brick(sf::Vector2f pos, sf::Vector2f size, int hp)
{
    if (hp < 1) hp = 1;
    if (hp > 3) hp = 3;

    life = hp;
    destroyed = false;

    setPosition(pos);
    setSize(size);
    setFillColor(LUT[life]);
    setOutlineColor(sf::Color::White);
    setOutlineThickness(1.f);
}

// Obs³uga trafienia w klocek
void Brick::trafienie()
{
    if (destroyed)
        return;

    life--;

    if (life <= 0)
    {
        destroyed = true;
        return;
    }

    else
    {
        setFillColor(LUT[life]);
    }
}


// Sprawdzenie, czy klocek zosta³ zniszczony
bool Brick::czyZniszczony() const
{
    return destroyed;
}

// Rysowanie klocka na ekranie, jeœli nie jest zniszczony
void Brick::draw(sf::RenderTarget& window)
{
    if (!destroyed)
        window.draw(*this);
}


