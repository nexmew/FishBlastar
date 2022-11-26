#include "Projectile.h"
#include "Configuration.h"

Projectile::Projectile()
{
	setFillColor(sf::Color::Red);
	setSize(sf::Vector2f(Config::ProjectileSize, Config::ProjectileSize));
	setOrigin(getSize() * 0.5f);
}

Projectile::~Projectile()
{
}

void Projectile::setDirection(Direction dir)
{
	mMovement = sf::Vector2f();
	switch (dir)
	{
	case Direction::Up:
		mMovement.y -= Config::ProjectileSpeed;
		break;
	case Direction::Down:
		mMovement.y += Config::ProjectileSpeed;
		break;
	case Direction::Left:
		mMovement.x -= Config::ProjectileSpeed;
		break;
	case Direction::Right:
		mMovement.x += Config::ProjectileSpeed;
		break;
	default:
		return;
	}
}

void Projectile::update(sf::Time deltaTime)
{
	move(mMovement * deltaTime.asSeconds());
}
