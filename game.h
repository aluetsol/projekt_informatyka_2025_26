#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "paddle.h"
#include "ball.h"
#include "brick.h"

//Klasa Game – zarz¹dza logik¹ gry: aktualizuje objekty, kolizjami, punktacj¹ i stanem gry
class Game
{
private:
    Paddle m_paletka;
    Ball m_pilka;
    std::vector<Brick> m_bloki;

    int score;
    sf::Font font;
    sf::Text scoreText;

    bool fontLoaded;
    sf::Vector2f blockSize;

public:
    Game();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    Game(Game&&) = default;
    Game& operator=(Game&&) = default;

    void loadLevel(sf::Vector2u windowSize);
    void update(sf::Time dt, sf::Vector2u windowSize);
    void render(sf::RenderTarget& target);

    bool isGameOver() const;
    bool isWin() const;

    Paddle& getPaddle() { return m_paletka; }
    Ball& getBall() { return m_pilka; }
    std::vector<Brick>& getBlocks() { return m_bloki; }
    sf::Vector2f getBlockSize() const { return blockSize; }
    sf::Font& getFont() { return font; }
    bool isFontLoaded() const { return fontLoaded; }

    int getScore() const { return score; }
    void setScore(int s)
    {
        score = s;
        if (fontLoaded)
            scoreText.setString("Wynik: " + std::to_string(score));
    }

};

