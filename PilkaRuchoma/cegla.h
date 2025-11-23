#pragma once

#include <SFML/Graphics.hpp>
#include <array> //prosta tablica stalego rozmiaru

class Cegla :public sf::RectangleShape
{
private:
	int punktyZycia; //0-3
	bool jestZniszczony; //jesli zniszczony to =true
	//sf::RectangleShape brick; //nie jest to potrzebne, nie programujemy w ten sposob
	static const std::array<sf::Color, 4> colorLUT; //tablica Look-up

public:
	Cegla(sf::Vector2f startPos, sf::Vector2f rozmiar, int liczbaZyc);
	void aktualizujKolor(); //zmiana koloru w zaleznosci od punktyZycia
	void trafienie(); //mechanizm aktualizacji punktow zycia
	void draw(sf::RenderTarget& window);
	bool czyZniszczony() { return jestZniszczony; };
};

Cegla::Cegla(sf::Vector2f startPos, sf::Vector2f rozmiar, int liczbaZyc)
{
	punktyZycia = liczbaZyc;
	jestZniszczony = false; //nie jest zniszczony
	this->setPosition(startPos);
	this->setSize(rozmiar);
	this->setFillColor(sf::Color::Yellow);
	this->setOutlineColor(sf::Color::White);
	aktualizujKolor();
}

const std::array<sf::Color, 4> Cegla::colorLUT =
{
	sf::Color::Transparent,
	sf::Color::Yellow,
	sf::Color::Magenta,
	sf::Color::Red
};

void Cegla::trafienie()
{
	if (jestZniszczony == true)
		return; //zakonczenie funkcji

	punktyZycia--;
	aktualizujKolor();
	if (punktyZycia <= 0)
		jestZniszczony = true;
}


void Cegla::aktualizujKolor()
{
	if (punktyZycia >= 0 && punktyZycia <= 3)
		this->setFillColor(colorLUT[punktyZycia]);
}

void Cegla::draw(sf::RenderTarget& window)
{
	window.draw(*this);
}