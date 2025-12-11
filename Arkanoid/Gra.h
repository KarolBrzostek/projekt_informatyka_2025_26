#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

#include "Paletka.h"
#include "Pilka.h"
#include "Cegla.h"
#include "Bloki.h"
#include "Menu.h"
#include "HUD.h"
#include "StanGry.h"
#include "Wyniki.h"

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
	Wyniki m_wyniki;
	int punkty = 0;

	bool pauza = false;
	bool pytanieWyjscie = false;

	bool koniec = false;

public:
	Gra();

	void update(sf::Time dt);
	void render(sf::RenderWindow& target);
	void reset(bool pokazKomunikatResetu);

	const Paletka& getPaletka() const { return m_paletka; };
	const Pilka& getPilka() const { return m_pilka; };
	const std::vector<Cegla>& getBlocks() const { return m_bloki.getBloki(); };
	HUD& getHUD() { return m_hud; };

	bool zapisz();
	bool wczytaj();

	bool czyPauza() const { return pauza; };
	bool pytanieWyjscia() const { return pytanieWyjscie; };

	void przelaczPauze();
	bool potwierdzWyjscie();
	bool getKoniec() { return koniec; };

	void startNowejGry();

};

Gra::Gra()
	:m_paletka({ SZEROKOSC / 2.f,WYSOKOSC - 100.f }, { 80,10 }, { 100,0 }),
	m_pilka({ SZEROKOSC / 2.f,WYSOKOSC - 200.f }, 10.f, { 100,100 }),
	m_bloki(12, 4, SZEROKOSC, WYSOKOSC)
{
	m_hud.ustawZycia(zycia);
	m_pilka.opoznienieRuchu();
	koniec = false;
	pauza = false;
	pytanieWyjscie = false;
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
			if (koniec == false)
			{
				m_wyniki.dodajWynik(punkty);
				koniec = true;
				std::remove("zapis.txt");
			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				reset(true);

				m_hud.ustawZycia(3);
			}

		}
	}

	punkty += m_bloki.sprawdzKolizje(m_pilka);
	m_bloki.usunZniszczoneBloki();
	m_hud.ustawPunkty(punkty);

	if (m_bloki.getBloki().empty())
	{
		m_hud.komunikatWygranej();
		if (koniec == false)
		{
			m_wyniki.dodajWynik(punkty);
			koniec = true;
			std::remove("zapis.txt");
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			reset(true);
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

void Gra::reset(bool pokazKomunikatResetu)
{
	zycia = 3;
	m_hud.ustawZycia(zycia);
	punkty = 0;
	m_hud.ustawPunkty(punkty);
	koniec = false;


	m_paletka.setPos({ SZEROKOSC / 2.f, WYSOKOSC - 100.f });

	m_pilka.setPos({ SZEROKOSC / 2.f,WYSOKOSC - 200.f });
	m_pilka.setVelocity({ 100.f,100.f });
	m_pilka.setCzySpadla();

	m_bloki = Bloki(LICZBA_KOLUMN, LICZBA_WIERSZY, SZEROKOSC, WYSOKOSC);

	if (pokazKomunikatResetu)
	{
		m_hud.komunikatResetu();
	}

	m_pilka.opoznienieRuchu();
}

bool Gra::zapisz()
{
	if (koniec)
	{
		return true;
	}
	StanGry snapshot(m_paletka, m_pilka, m_bloki.getBloki(), zycia, punkty);

	if (snapshot.saveToFile("zapis.txt"))
	{
		m_hud.komunikatZapisu();
		return true;
	}
	return false;
}

bool Gra::wczytaj()
{
	if (koniec)
	{
		return false;
	}
	StanGry snapshot(m_paletka, m_pilka, m_bloki.getBloki(), zycia, punkty);
	if (snapshot.loadFromFile("zapis.txt"))
	{
		snapshot.apply(m_paletka, m_pilka, m_bloki, zycia, punkty);
		m_hud.ustawZycia(zycia);
		m_hud.ustawPunkty(punkty);
		koniec = false;
		m_pilka.opoznienieRuchu();
		m_hud.komunikatWczytania();
		return true;
	}
	return false;
}

void Gra::przelaczPauze()
{
	if (!pauza)
	{
		pauza = true;
		pytanieWyjscie = true;
		m_hud.ustawPauze(pauza);
	}
	else
	{
		pauza = false;
		pytanieWyjscie = false;
		m_hud.ustawPauze(false);
	}
}

bool Gra::potwierdzWyjscie()
{
	if (pauza && pytanieWyjscie)
	{
		pauza = false;
		pytanieWyjscie = false;
		m_hud.ustawPauze(pauza);
		return true;
	}
	return false;
}

void Gra::startNowejGry()
{
	reset(false);
	m_pilka.opoznienieRuchu();
	m_hud.komunikatNowejGry();
}