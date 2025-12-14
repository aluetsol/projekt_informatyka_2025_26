#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "paddle.h"
#include "ball.h"
#include "brick.h"

// Struktura BlockData – przechowuje dane pojedynczego klocka
struct BlockData
{
	float x;
	float y;
	int hp;
};

// Klasa GameState – zarz¹dza zapisem i wczytywaniem stanu gry
class GameState
{
private:
	sf::Vector2f paddlePosition;
	sf::Vector2f ballPosition;
	sf::Vector2f ballVelocity;
	int savedScore = 0;

public:
	std::vector<BlockData> blocks;
	GameState() = default;

	void capture(const Paddle& p, const Ball& b, const std::vector<Brick>& stones, int score);
	bool saveToFile(const std::string& filename) const;
	bool loadFromFile(const std::string& filename);
	void apply(Paddle& p, Ball& b, std::vector<Brick>& stones, sf::Vector2f blockSize) const;
	int getSavedScore() const { return savedScore; }
};

