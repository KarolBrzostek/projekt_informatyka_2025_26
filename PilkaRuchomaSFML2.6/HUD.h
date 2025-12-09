#pragma once
#include <SFML/Graphics.hpp>

class HUD
{
public:
	HUD();
	void komunikatZapisu();
	void komunikatWczytania();
	void komunikatPorazki();
	void komunikatResetu();

	void update();
	void draw(sf::RenderTarget& window);

private:
	sf::Font font;
	sf::Text komunikat;
	sf::Clock timer;
	bool widoczny = false;
	void pokazKomunikat(const std::string& text, sf::Color color);
};

HUD::HUD()
{
	font.loadFromFile("arial.ttf");

	komunikat.setFont(font);
	komunikat.setCharacterSize(28);
	komunikat.setStyle(sf::Text::Bold);
	komunikat.setPosition(20.f, 20.f);
	komunikat.setOutlineColor(sf::Color::Black);
	komunikat.setOutlineThickness(2);
}

void HUD::pokazKomunikat(const std::string& text, sf::Color color)
{
	komunikat.setFillColor(color);
	komunikat.setString(text);
	timer.restart();
	widoczny = true;
}

void HUD::komunikatZapisu()
{
	pokazKomunikat("Gra zapisana!", sf::Color::Yellow);
}

void HUD::komunikatWczytania()
{
	pokazKomunikat("Wczytano ostatni zapis.", sf::Color::Green);
}

void HUD::komunikatPorazki()
{
	pokazKomunikat("Porazka! Pilka spadla.", sf::Color::Red);
}

void HUD::komunikatResetu()
{
	pokazKomunikat("Zresetowano gre.", sf::Color::Red);
}

void HUD::update()
{
	if (widoczny == true && timer.getElapsedTime().asSeconds() > 2.0f)
	{
		widoczny = false;
	}
}

void HUD::draw(sf::RenderTarget& window)
{
	if (widoczny == true)
	{
		window.draw(komunikat);
	}
}

