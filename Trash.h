#pragma once

#include "DynamicObject.h"

class Trash : public DynamicObject
{
public:
	Trash();
	~Trash();

	void update(sf::Time deltaTime) override;

private:
	sf::Texture mTex;
};

