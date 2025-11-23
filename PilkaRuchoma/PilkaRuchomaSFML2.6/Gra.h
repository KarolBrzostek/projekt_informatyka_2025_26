#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>


#include "Paletka.h"
#include "Pilka.h"
#include "Cegla.h"
#include "Bloki.h"
#include "Menu.h"

class Gra
{
private:

	//rozmiary
	const int WYSOKOSC=600;
	const int SZEROKOSC=800;
	const int LICZBA_KOLUMN=12;
	const int LICZBA_WIERSZY=4;

	
	sf::Clock m_deltaClk;

	//obiekty
	Paletka m_paletka;
	Pilka m_pilka;
	Bloki m_bloki;

	
public:
	Gra();

	void update(sf::Time dt);
	void render(sf::RenderWindow& target);
};

Gra::Gra()
	:m_paletka({ SZEROKOSC / 2.f,WYSOKOSC - 100.f }, { 80,10 }, { 100,0 }),
	m_pilka({ SZEROKOSC / 2.f,WYSOKOSC - 200.f }, 10.f, { 100,100 }),
	m_bloki(12, 4, SZEROKOSC, WYSOKOSC)
{
}

void Gra::update(sf::Time dt)
{

	m_paletka.ruch(dt, { 800.f,600.f });
	m_pilka.ruch(dt, { 800.f,600.f }, m_paletka, { 800 / 2.f,600 - 200.f });

	m_bloki.sprawdzKolizje(m_pilka);
	m_bloki.usunZniszczoneBloki();
}

void Gra::render(sf::RenderWindow& target)
{
	m_paletka.draw(target);
	m_pilka.draw(target);

	//rysowanie blokow
	m_bloki.rysujBloki(target);

}