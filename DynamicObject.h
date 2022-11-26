#pragma once

#include <SFML\Graphics.hpp>

class DynamicObject : public sf::RectangleShape
{
public:
	void setActive(bool active) { mActive = active; }
	bool isActive() const { return mActive; }

	virtual void update(sf::Time deltaTime) = 0;

protected:
	bool mActive = false;
};