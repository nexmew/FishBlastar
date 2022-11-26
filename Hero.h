#pragma once

#include <functional>
#include "DynamicObject.h"
#include "Direction.h"

class Hero : public DynamicObject
{
public:
	Hero(std::function<void(sf::Vector2f, Direction)> spawner);
	~Hero();

	void update(sf::Time deltaTime) override;

private:
    sf::Vector2f getProjectilePos() const;

private:
	sf::Texture mTex;
	Direction mDir;

	std::function<void(sf::Vector2f, Direction)> mSpawner;
};

