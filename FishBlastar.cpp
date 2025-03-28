#include <memory>
#include <SFML\Graphics.hpp>
#include "Configuration.h"
#include "Level.h"

int WinMain()
{
	auto videoMode = sf::VideoMode((int)Config::WindowWidth, (int)Config::WindowHeight);
    sf::RenderWindow window(videoMode, Config::WindowTitle);

    Level level;

	const sf::Time updateTime = sf::seconds(1.f / Config::MaxFramerate);
	sf::Clock frameClock;
	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
                window.close();
			}
		}

		if (frameClock.getElapsedTime() >= updateTime)
		{
			frameClock.restart();

			if (window.hasFocus())
			{
				level.update(updateTime);
			}
		}

        window.clear();
        window.draw(level);
        window.display();
	}

    return 0;
}
