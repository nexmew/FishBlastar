#include "Hero.h"
#include "Configuration.h"

Hero::Hero(std::function<void(sf::Vector2f, Direction)> spawner)
{
	mDir = Direction::Right;
	mSpawner = spawner;
	mTex.loadFromFile(Config::HeroImage);
	auto texSize = mTex.getSize();

	setTexture(&mTex, true);
	setSize(sf::Vector2f(static_cast<float>(texSize.x), static_cast<float>(texSize.y)));
	setOrigin(getSize() * 0.5f);
}

Hero::~Hero()
{
}

void Hero::update(sf::Time deltaTime)
{
	sf::Vector2f scale(1, 1);
	sf::Vector2f movement(0, 0);
	float rotation = 0;
	Direction dir = Direction::None;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		dir = Direction::Up;
		movement.y -= Config::HeroSpeed;
		rotation = -90;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		dir = Direction::Down;
		movement.y += Config::HeroSpeed;
		rotation = 90;
		scale.y = -1;
    }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		dir = Direction::Left;
		movement.x -= Config::HeroSpeed;
		scale.x = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		dir = Direction::Right;
		movement.x += Config::HeroSpeed;
	}

	if (dir != Direction::None)
	{
		mDir = dir;
		setScale(scale);
		setRotation(rotation);
		move(movement * deltaTime.asSeconds());
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		mSpawner(getProjectilePos(), mDir);
	}
}

sf::Vector2f Hero::getProjectilePos() const
{
    sf::Vector2f projectilePos = getPosition();
    switch (mDir)
    {
    case Direction::Up:
        projectilePos.y -= getSize().y * 0.5f;
        break;
    case Direction::Down:
        projectilePos.y += getSize().y * 0.5f;
        break;
    case Direction::Left:
        projectilePos.x -= getSize().x * 0.5f;
        break;
    case Direction::Right:
        projectilePos.x += getSize().x * 0.5f;
        break;
    }
    return projectilePos;
}
