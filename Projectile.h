#pragma once

#include "DynamicObject.h"
#include "Direction.h"

class Projectile : public DynamicObject
{
public:
	Projectile();
	~Projectile();

	void update(sf::Time deltaTime) override;
	void setDirection(Direction dir);
	
private:
	sf::Vector2f mMovement;
};

