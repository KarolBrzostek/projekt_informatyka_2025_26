#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>


#include "Paletka.h"
#include "Pilka.h"
#include "Cegla.h"
#include "Bloki.h"

class Gra
{
private:

	//rozmiary
	const int WYSOKOSC=600;
	const int SZEROKOSC=800;
	const int LICZBA_KOLUMN=12;
	const int LICZBA_WIERSZY=4;

	sf::RenderWindow m_window;
	sf::Clock m_deltaClk;
	sf::Time czas;

	//obiekty
	Paletka m_paletka;
	Pilka m_pilka;
	Bloki m_bloki;

	void processEvents();
	void update();
	void render();
public:
	Gra();
	void run();

};

Gra::Gra()
	: m_window(sf::VideoMode(SZEROKOSC,WYSOKOSC), "Gra v0.2"),
	m_paletka({ SZEROKOSC / 2.f,WYSOKOSC - 100.f }, { 80,10 }, { 100,0 }),
	m_pilka({ SZEROKOSC / 2.f,WYSOKOSC - 200.f }, 10.f, { 100,100 }),
	m_bloki(12, 4, SZEROKOSC, WYSOKOSC)
{
	m_window.setFramerateLimit(60);
}

void Gra::run()
{
	while (m_window.isOpen())
	{
		processEvents();
		update();
		render();
	}
}


void Gra::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window.close();
	}
}

void Gra::update()
{
	czas = m_deltaClk.restart();

	m_paletka.ruch(czas, { 800.f,600.f });
	m_pilka.ruch(czas, { 800.f,600.f }, m_paletka, { 800 / 2.f,600 - 200.f });

	m_bloki.sprawdzKolizje(m_pilka);
	m_bloki.usunZniszczoneBloki();
}

void Gra::render()
{
	m_window.clear();
	m_paletka.draw(m_window);
	m_pilka.draw(m_window);

	//rysowanie blokow
	m_bloki.rysujBloki(m_window);

	m_window.display();
}