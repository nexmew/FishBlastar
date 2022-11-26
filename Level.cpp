#include "Level.h"
#include <functional>
#include <random>
#include "Configuration.h"


Level::Level()
{
	mIsGameOver = false;

	mHero = std::make_unique<Hero>(std::bind(&Level::spawnProjectile, this, std::placeholders::_1, std::placeholders::_2));
	mProjectiles.resize(Config::MaxProjectilesCount);
	mTrashes.resize(Config::MaxTrashesCount);

	auto skySize = sf::Vector2f(Config::WindowWidth, Config::WindowHeight * 0.25f);
	mSky.setOrigin(sf::Vector2f());
	mSky.setPosition(sf::Vector2f());
	mSky.setSize(skySize);
	mSky.setFillColor(sf::Color(Config::SkyColor));

	auto seaSize = sf::Vector2f(Config::WindowWidth, Config::WindowHeight * 0.75f);
	mSea.setOrigin(sf::Vector2f());
	mSea.setPosition(sf::Vector2f(0, skySize.y));
	mSea.setSize(seaSize);
	mSea.setFillColor(sf::Color(Config::SeaColor));

	mFont.loadFromFile(Config::FontPath);

    mPopup = std::make_unique<Popup>(std::bind(&Level::reset, this), mFont);

    mPointsText.setFillColor(sf::Color::Black);
    mPointsText.setFont(mFont);
    mPointsText.setPosition(skySize.x - 200, 20);

    reset();
}

Level::~Level()
{
}

void Level::update(sf::Time deltaTime)
{
	if (mIsGameOver)
	{
        mPopup->update(deltaTime);
		return;
	}

	mTrashSpawnPeriod += deltaTime;
	if (mTrashSpawnPeriod > sf::seconds(Config::TrashSpawnPeriod))
	{
		mTrashSpawnPeriod = sf::Time::Zero;
		spawnTrash();
	}

	mHero->update(deltaTime);

	for (auto& projectile : mProjectiles)
	{
		if (projectile.isActive())
			projectile.update(deltaTime);
	}

	for (auto& trash : mTrashes)
	{
		if (trash.isActive())
			trash.update(deltaTime);
	}

	checkHeroPosition();
	checkProjectilesPosition();
	checkTrashesPosition();

    mPointsText.setString("Points: " + std::to_string(mPoints));
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSky);
	target.draw(mSea);

    target.draw(mPointsText);

	target.draw(*mHero);

	for (const auto& projectile : mProjectiles)
	{
		if (projectile.isActive())
			target.draw(projectile);
	}

	for (const auto& trash : mTrashes)
	{
		if (trash.isActive())
			target.draw(trash);
	}

    if (mIsGameOver)
    {
        target.draw(*mPopup);
    }
}

void Level::spawnProjectile(sf::Vector2f position, Direction direction)
{
	auto it = std::find_if(mProjectiles.begin(), mProjectiles.end(), [](auto p) { return !p.isActive(); });
	if (it == mProjectiles.end())
		return; //can't spawn new one due to limits

	it->setPosition(position);
	it->setDirection(direction);
	it->setActive(true);
}

void Level::spawnTrash()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(Config::TrashSpawnOffset, mSea.getSize().x - Config::TrashSpawnOffset);

	auto it = std::find_if(mTrashes.begin(), mTrashes.end(), [](auto p) { return !p.isActive(); });
	if (it == mTrashes.end())
		return; //can't spawn new one due to limits

	it->setPosition(sf::Vector2f(static_cast<float>(dis(gen)), Config::TrashSpawnOffset));
	it->setActive(true);
}

void Level::checkHeroPosition()
{
    auto pos = mHero->getPosition();
    auto heroBounds = mHero->getGlobalBounds();
    auto bounds = mSea.getGlobalBounds();
    
    if (heroBounds.left < bounds.left)
    {
        pos.x -= heroBounds.left - bounds.left;
    }
    else if ((heroBounds.left + heroBounds.width) > (bounds.left + bounds.width))
    {
        pos.x -= (heroBounds.left + heroBounds.width) - (bounds.left + bounds.width);
    }

    if (heroBounds.top < bounds.top)
    {
        pos.y -= heroBounds.top - bounds.top;
    }
    else if ((heroBounds.top + heroBounds.height) >(bounds.top + bounds.height))
    {
        pos.y -= (heroBounds.top + heroBounds.height) - (bounds.top + bounds.height);
    }

    mHero->setPosition(pos);
}

void Level::checkProjectilesPosition()
{
    auto seaBounds = mSea.getGlobalBounds();
    for (auto& projectile : mProjectiles)
    {
        if (!projectile.isActive())
            continue;

        auto bounds = projectile.getGlobalBounds();
        if (!seaBounds.intersects(bounds))
        {
            projectile.setActive(false);
            continue;
        }

        for (auto& trash : mTrashes)
        {
            if (trash.getGlobalBounds().intersects(bounds))
            {
                projectile.setActive(false);
                trash.setActive(false);
                ++mPoints;
                break;
            }
        }
    }
}

void Level::checkTrashesPosition()
{
    auto heroBounds = mHero->getGlobalBounds();
    auto groundPos = mSea.getPosition().y + mSea.getSize().y;
    for (const auto& trash : mTrashes)
    {
        if (!trash.isActive())
            continue;

        if (groundPos > trash.getPosition().y && !trash.getGlobalBounds().intersects(heroBounds))
            continue;

        gameOver();
        break;
    }
}

void Level::gameOver()
{
    mPopup->setPointsText(std::to_string(mPoints));
    mIsGameOver = true;
}

void Level::reset()
{
    mPoints = 0;
    mIsGameOver = false;
    mTrashSpawnPeriod = sf::Time::Zero;

    mHero->setPosition(mSea.getPosition() + mSea.getSize() * 0.5f);
    for (auto& trash : mTrashes)
    {
        trash.setActive(false);
    }
    for (auto& projectile : mProjectiles)
    {
        projectile.setActive(false);
    }
}
