#pragma once
#include <SFML/Graphics.hpp>

class HUD
{
public:
	HUD();

	void pokazKomunikat(const std::string& text, sf::Color color);
	void komunikatZapisu();
	void komunikatWczytania();
	void komunikatPorazki();
	void komunikatResetu();
	void komunikatWygranej();

	void update();
	void draw(sf::RenderTarget& window);

	void ustawZycia(int liczba);

private:
	sf::Font font;
	sf::Text komunikat;
	sf::Clock timer;

	bool widoczny = false;
	float alpha = 255.f;

	sf::Texture sercePelne;
	sf::Texture sercePuste;
	std::vector<sf::Sprite> serca;
};

HUD::HUD()
{
	font.loadFromFile("arial.ttf");

	sercePelne.loadFromFile("sercePelne.png");
	sercePuste.loadFromFile("sercePuste.png");

	serca.resize(3);
	for (int i = 0; i < 3; i++)
	{
		serca[i].setPosition(680 + i * 40, 20);
		serca[i].setTexture(sercePelne);
	}

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
	alpha = 255.f;
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
	pokazKomunikat("Porazka! Straciles wszystkie zycia!", sf::Color::Red);
}

void HUD::komunikatResetu()
{
	pokazKomunikat("Zresetowano gre.", sf::Color::Red);
}

void HUD::komunikatWygranej()
{
	pokazKomunikat("Wygrales! Wszystkie bloki zniszczone!", sf::Color::Green);
}

void HUD::update()
{
	if (!widoczny) return;

	float t = timer.getElapsedTime().asSeconds();

	if (t > 1.0f)
	{
		alpha = 255.f - (t - 1.0f) * 255.f;

		if (alpha <= 0.f)
		{
			alpha = 0.f;
			widoczny = false;
		}

		sf::Color c;
		c = komunikat.getFillColor();
		c.a = static_cast<sf::Uint8>(alpha);
		komunikat.setFillColor(c);
	}
}

void HUD::draw(sf::RenderTarget& window)
{
	for (auto& h : serca)
	{
		window.draw(h);
	}
	if (widoczny == true)
	{
		window.draw(komunikat);
	}
}

void HUD::ustawZycia(int liczba)
{
	for (int i = 0; i < 3; i++)
	{
		if (i < liczba)
		{
			serca[i].setTexture(sercePelne);
		}
		else
		{
			serca[i].setTexture(sercePuste);
		}
	}
}