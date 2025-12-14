#include <fstream>
#include <iostream>
#include "GameState.h"

// Zapisuje aktualny stan gry: pozycjê paletki, pi³ki, wynik i stan klocków
void GameState::capture(const Paddle& p, const Ball& b, const std::vector<Brick>& stones, int score)
{
	paddlePosition = p.getPosition();
	ballPosition = b.getPosition();
	ballVelocity = b.getVelocity();
	savedScore = score;

	blocks.clear();
	for (const auto& blk : stones)
	{
		blocks.push_back(
			{
				blk.getPosition().x,
				blk.getPosition().y,
				blk.getHP()
			});
	}
}

// Zapisuje stan gry do pliku tekstowego
bool GameState::saveToFile(const std::string& filename) const
{
	std::ofstream file(filename);
	if (!file.is_open())
		return false;

	file << "PADDLE " << paddlePosition.x << " " << paddlePosition.y << "\n";
	file << "BALL " << ballPosition.x << " " << ballPosition.y << " " << ballVelocity.x << " " << ballVelocity.y << "\n";
	file << "SCORE " << savedScore << "\n";
	file << "BLOCKS_COUNT " << blocks.size() << "\n";

	for (const auto& b : blocks)
		file << b.x << " " << b.y << " " << b.hp << "\n";

	file.close();
	return file.good();
}

// Wczytuje stan gry z pliku tekstowego
bool GameState::loadFromFile(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open()) return false;

	std::string label;
	if (!(file >> label >> paddlePosition.x >> paddlePosition.y))
	{
		file.close();  return false;
	}
	if (!(file >> label >> ballPosition.x >> ballPosition.y >> ballVelocity.x >> ballVelocity.y))
	{
		file.close();  return false;
	}
	if (!(file >> label >> savedScore))
	{
		file.close();  return false;
	}

	int count = 0;
	if (!(file >> label >> count))
	{
		file.close();  return false;
	}

	blocks.clear();
	for (int i = 0; i < count; ++i)
	{
		float x, y; int hp;
		if (!(file >> x >> y >> hp))
		{
			file.close();  return false;
		}
		blocks.push_back({ x,y,hp });
	}
	file.close();
	return true;
}

// Przywraca zapisany stan gry do podanych obiektów gry
void GameState::apply(Paddle& p, Ball& b, std::vector<Brick>& stones, sf::Vector2f blockSize) const
{
	p.setPosition(paddlePosition);
	b.setState(ballPosition, ballVelocity);

	stones.clear();
	for (const auto& bd : blocks)
		stones.emplace_back(sf::Vector2f(bd.x, bd.y), blockSize, bd.hp);
}
