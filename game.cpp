#include <iostream>
#include "game.h"
#include <filesystem>

// Konstruktor klasy Game – inicjalizuje paletkê, pi³kê, wynik i wczytuje czcionkê
Game::Game()
    :m_paletka({ 400.f, 550.f }, { 200.f, 20.f }, { 300.f, 0.f }),
    m_pilka({ 400.f, 300.f }, 20.f, { 200.f, 200.f }),
    score(0),
    fontLoaded(false)
{
    std::cout << "WORKING DIR = " << std::filesystem::current_path() << std::endl;

    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "ERROR: nie mozna wczytac arial.ttf." << std::endl;
        fontLoaded = false;

    }
    else
    {
        std::cout << "Font OK" << std::endl;
        fontLoaded = true;

        scoreText.setFont(font);
        scoreText.setCharacterSize(26);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(10.f, 10.f);
        scoreText.setString("Wynik: 0");
    }
    loadLevel({ 800, 600 });
}

// Wczytywanie poziomu – tworzy klocki i ustawia ich pozycje oraz ¿ywotnoœæ
void Game::loadLevel(sf::Vector2u windowSize)
{
    m_bloki.clear();

    const int COLS = 12;
    const int ROWS = 4;
    float blockW = (windowSize.x - (COLS - 1) * 2.f) / COLS;
    float blockH = 20.f;
    blockSize = { blockW, blockH };

    for (int y = 0; y < ROWS; y++)
    {
        for (int x = 0; x < COLS; x++)
        {
            float px = static_cast<float>(x) * (blockW + 2.f);
            float py = static_cast<float>(y) * (blockH + 2.f) + 60.f;
            int life = 3 - y;
            if (life < 1) life = 1;

            m_bloki.emplace_back
            (
                sf::Vector2f(px, py),
                sf::Vector2f(blockW, blockH),
                life
            );
        }
    }
}

// Aktualizacja stanu gry – ruch paletki, pi³ki i obs³uga kolizji z klockami
void Game::update(sf::Time dt, sf::Vector2u windowSize)
{
    m_paletka.ruch(dt, sf::Vector2f(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)));
    m_pilka.ruch(dt, sf::Vector2f(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)), m_paletka);

    for (auto it = m_bloki.begin(); it != m_bloki.end(); )
    {
        if (m_pilka.getGlobalBounds().intersects(it->getGlobalBounds()))
        {
            it->trafienie();
            m_pilka.odbijY();

            if (it->czyZniszczony())
            {
                score += 10;
                if (fontLoaded)
                    scoreText.setString("Wynik: " + std::to_string(score));

                it = m_bloki.erase(it);
                continue;
            }
        }

        ++it;
    }

}

// Rysowanie obiektów gry na ekranie
void Game::render(sf::RenderTarget& target)
{
    m_paletka.draw(target);
    m_pilka.draw(target);

    for (auto& blk : m_bloki)
    {
        if (!blk.czyZniszczony())
            blk.draw(target);
    }

    if (fontLoaded)
    {
        target.draw(scoreText);
    }
}

// Sprawdzenie, czy gra siê zakoñczy³a (pi³ka poza doln¹ krawêdzi¹ ekranu)
bool Game::isGameOver() const
{
    return m_pilka.getPosition().y > 600.f;
}

// Sprawdzenie, czy gracz wygra³ (wszystkie klocki zniszczone)
bool Game::isWin() const
{
    return m_bloki.empty();
}


