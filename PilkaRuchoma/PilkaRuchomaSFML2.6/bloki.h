#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

#include "paletka.h"
#include "pilka.h"
#include "cegla.h"

class Bloki
{
public:
	Bloki(int liczbaKolumn, int liczbaWierszy, float szerokoscOkna, float wysokoscOkna);
	void rysujBloki(sf::RenderTarget& window);
	void sprawdzKolizje(Pilka& pilka);
	void usunZniszczoneBloki();
	std::vector<Cegla>& getBloki();

private:
	std::vector<Cegla> bloki;
	float rozmiarX;
	float rozmiarY;
	int LICZBA_WIERSZY;
	int LICZBA_KOLUMN;
};

Bloki::Bloki(int liczbaKolumn, int liczbaWierszy, float szerokoscOkna, float wysokoscOkna)
{
	LICZBA_KOLUMN = liczbaKolumn;
	LICZBA_WIERSZY = liczbaWierszy;
	rozmiarX = ((szerokoscOkna - (LICZBA_KOLUMN - 1) * 2.f) / LICZBA_KOLUMN);
	rozmiarY = 20.f;

	for (int y = 0; y < LICZBA_WIERSZY; y++)
	{
		for (int x = 0; x < LICZBA_KOLUMN; x++)
		{
			float posX = x * (rozmiarX + 2.f);
			float posY = y * (rozmiarY + 2.f) + 60.f;

			int zycie = 0;
			if (y == 0)
				zycie = 3;
			if (y == 1)
				zycie = 2;
			if (y >= 2)
				zycie = 1;

			bloki.emplace_back(sf::Vector2f(posX, posY), sf::Vector2f(rozmiarX, rozmiarY), zycie);
		}

	}
}

void Bloki::rysujBloki(sf::RenderTarget& window)
{
	for (auto& blk : bloki)
	{
		blk.draw(window);
	}
}

void Bloki::sprawdzKolizje(Pilka& pilka)
{

	for (auto& blk : bloki)
	{
		sf::FloatRect graniceBLK = blk.getGlobalBounds();
		sf::FloatRect granicePilki = pilka.getBounds();

		if (!blk.czyZniszczony() && granicePilki.intersects(graniceBLK))
		{
			blk.trafienie(); //zmniejsza ilosc zyc i zmienia kolor
			pilka.odbijY();
		}
	}
}




void Bloki::usunZniszczoneBloki()
{
	for (int i = bloki.size() - 1; i >= 0; i--)
	{
		if (bloki[i].czyZniszczony())
		{
			bloki.erase(bloki.begin() + i);
		}
	}
}

std::vector<Cegla>& Bloki::getBloki()
{
	return bloki;
}