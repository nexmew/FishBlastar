#include "Popup.h"
#include "Configuration.h"

Popup::Popup(std::function<void()> restartFunc, const sf::Font& font)
{
    mRestartFunc = restartFunc;

    mTitle.setFont(font);
    mTitle.setFillColor(sf::Color::Black);
    mTitle.setString(Config::PopupTitle);
    mTitle.setOrigin(mTitle.getGlobalBounds().width * 0.5f, mTitle.getGlobalBounds().height * 0.5f);
    mTitle.setPosition(Config::WindowWidth * 0.5f, Config::WindowHeight * 0.5f - 75);

    mPoints.setFont(font);
    mPoints.setFillColor(sf::Color::Blue);
    setPointsText("Points: 0");

    mTipText.setFont(font);
    mTipText.setFillColor(sf::Color::Yellow);
    mTipText.setString(Config::PopupTipLabel);
    mTipText.setOrigin(mTipText.getGlobalBounds().width * 0.5f, mTipText.getGlobalBounds().height * 0.5f);
    mTipText.setPosition(mPoints.getPosition() + sf::Vector2f(0, 50));

    mRestartBtnLabel.setFont(font);
    mRestartBtnLabel.setFillColor(sf::Color::Black);
    mRestartBtnLabel.setString(Config::PopupRestart);
    mRestartBtnLabel.setOrigin(mRestartBtnLabel.getGlobalBounds().width * 0.5f, mRestartBtnLabel.getGlobalBounds().height * 0.5f);
    mRestartBtnLabel.setPosition(mTipText.getPosition() + sf::Vector2f(0, 75));

    mBorder.setFillColor(sf::Color::Cyan);
    mBorder.setSize(sf::Vector2f(500, 300));
    mBorder.setOrigin(mBorder.getSize() * 0.5f);
    mBorder.setPosition(Config::WindowWidth * 0.5f, Config::WindowHeight * 0.5f);

    mRestartBtn.setFillColor(sf::Color::Green);
    mRestartBtn.setSize(sf::Vector2f(200, 50));
    mRestartBtn.setOrigin(mRestartBtn.getSize() * 0.5f);
    mRestartBtn.setPosition(mRestartBtnLabel.getPosition());
}

Popup::~Popup()
{
}

void Popup::setPointsText(const std::string& text)
{
    mPoints.setString("Points: " + text);
    mPoints.setOrigin(mPoints.getGlobalBounds().width * 0.5f, mPoints.getGlobalBounds().height * 0.5f);
    mPoints.setPosition(mTitle.getPosition() + sf::Vector2f(0, 50));
}

void Popup::update(sf::Time deltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        mRestartFunc();
    }
}

void Popup::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mBorder);
    target.draw(mRestartBtn);
    target.draw(mTitle);
    target.draw(mPoints);
    target.draw(mTipText);
    target.draw(mRestartBtnLabel);
}
