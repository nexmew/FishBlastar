#pragma once

#include <SFML\Graphics.hpp>
#include <functional>

class Popup : public sf::Drawable
{
public:
	Popup(std::function<void()> restartFunc, const sf::Font& font);
	~Popup();

    void setPointsText(const std::string& text);
    void update(sf::Time deltaTime);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Text mTitle;
    sf::Text mPoints;
    sf::Text mRestartBtnLabel;
    sf::Text mTipText;
    sf::RectangleShape mBorder;
    sf::RectangleShape mRestartBtn;
    std::function<void()> mRestartFunc;
};

