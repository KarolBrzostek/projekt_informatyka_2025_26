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
#include "HUD.h"
#include "StanGry.h"

class Gra
{
private:

	//rozmiary
	const int WYSOKOSC = 600;
	const int SZEROKOSC = 800;
	const int LICZBA_KOLUMN = 12;
	const int LICZBA_WIERSZY = 4;

	int zycia = 3;

	sf::Clock m_deltaClk;


	//obiekty
	Paletka m_paletka;
	Pilka m_pilka;
	Bloki m_bloki;
	HUD m_hud;

public:
	Gra();

	void update(sf::Time dt);
	void render(sf::RenderWindow& target);
	void reset();

	const Paletka& getPaletka() const { return m_paletka; };
	const Pilka& getPilka() const { return m_pilka; };
	const std::vector<Cegla>& getBlocks() const { return m_bloki.getBloki(); };
	HUD& getHUD() { return m_hud; };

	bool zapisz();
	bool wczytaj();
};

Gra::Gra()
	:m_paletka({ SZEROKOSC / 2.f,WYSOKOSC - 100.f }, { 80,10 }, { 100,0 }),
	m_pilka({ SZEROKOSC / 2.f,WYSOKOSC - 200.f }, 10.f, { 100,100 }),
	m_bloki(12, 4, SZEROKOSC, WYSOKOSC)
{
	m_hud.ustawZycia(zycia);
	m_pilka.opoznienieRuchu();
}

void Gra::update(sf::Time dt)
{

	m_paletka.ruch(dt, { 800.f,600.f });
	m_pilka.ruch(dt, { 800.f,600.f }, m_paletka, { 800 / 2.f,600 - 200.f });

	if (m_pilka.pilkaSpadla() == true)
	{
		zycia--;
		m_hud.ustawZycia(zycia);
		if (zycia > 0)
		{
			m_pilka.setPos({ SZEROKOSC / 2.f,WYSOKOSC - 200.f });
			m_pilka.setVelocity({ 100.f,100.f });
			m_pilka.setCzySpadla();
			m_pilka.opoznienieRuchu();
		}
		else
		{
			m_hud.komunikatPorazki();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				reset();

				m_hud.ustawZycia(3);
			}

		}
	}

	m_bloki.sprawdzKolizje(m_pilka);
	m_bloki.usunZniszczoneBloki();

	if (m_bloki.getBloki().empty())
	{
		m_hud.komunikatWygranej();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			reset();
			return;
		}

		m_pilka.setVelocity({ 0,0 });
		return;
	}

	m_hud.update();
}

void Gra::render(sf::RenderWindow& target)
{
	m_paletka.draw(target);
	m_pilka.draw(target);

	//rysowanie blokow
	m_bloki.rysujBloki(target);

	m_hud.draw(target);

}

void Gra::reset()
{
	zycia = 3;
	m_hud.ustawZycia(zycia);

	m_paletka.setPos({ SZEROKOSC / 2.f, WYSOKOSC - 100.f });

	m_pilka.setPos({ SZEROKOSC / 2.f,WYSOKOSC - 200.f });
	m_pilka.setVelocity({ 100.f,100.f });
	m_pilka.setCzySpadla();

	m_bloki = Bloki(LICZBA_KOLUMN, LICZBA_WIERSZY, SZEROKOSC, WYSOKOSC);

	m_hud.komunikatResetu();
	m_pilka.opoznienieRuchu();
}

bool Gra::zapisz()
{
	StanGry snapshot(m_paletka, m_pilka, m_bloki.getBloki(), zycia);

	if (snapshot.saveToFile("zapis.txt"))
	{
		m_hud.komunikatZapisu();
		return true;
	}
	return false;
}

bool Gra::wczytaj()
{
	StanGry snapshot(m_paletka, m_pilka, m_bloki.getBloki(), zycia);
	if (snapshot.loadFromFile("zapis.txt"))
	{
		snapshot.apply(m_paletka, m_pilka, m_bloki, zycia);
		m_hud.ustawZycia(zycia);
		m_pilka.opoznienieRuchu();
		m_hud.komunikatWczytania();
		return true;
	}
	return false;
}