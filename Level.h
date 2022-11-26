#pragma once

#include <memory>
#include <list>
#include <SFML\Graphics.hpp>
#include "Hero.h"
#include "Projectile.h"
#include "Trash.h"
#include "Popup.h"
#include "Direction.h"

class Level : public sf::Drawable
{
public:
	Level();
	~Level() override;

	void update(sf::Time deltaTime);

protected:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	void spawnProjectile(sf::Vector2f position, Direction direction);
	void spawnTrash();
	void checkHeroPosition();
	void checkProjectilesPosition();
	void checkTrashesPosition();
    void gameOver();
    void reset();

private:
	bool mIsGameOver;
    unsigned int mPoints;
	sf::Time mTrashSpawnPeriod;

	sf::RectangleShape mSky;
	sf::RectangleShape mSea;
    sf::Text mPointsText;
	sf::Font mFont;

	std::unique_ptr<Popup> mPopup;
	std::unique_ptr<Hero> mHero;
	std::vector<Projectile> mProjectiles;
	std::vector<Trash> mTrashes;
};

