#include "Trash.h"
#include "Configuration.h"

Trash::Trash()
{
    static int tile_gen = 0;

    mTex.loadFromFile((tile_gen % 2 == 0) ? Config::Trash1Image : Config::Trash2Image);
	auto texSize = mTex.getSize();

    ++tile_gen;

	setTexture(&mTex, true);
	setSize(sf::Vector2f(static_cast<float>(texSize.x), static_cast<float>(texSize.y)));
	setOrigin(getSize().x * 0.5f, getSize().y);
}

Trash::~Trash()
{
}

void Trash::update(sf::Time deltaTime)
{
	move(sf::Vector2f(0, Config::TrashSpeed) * deltaTime.asSeconds());
}
