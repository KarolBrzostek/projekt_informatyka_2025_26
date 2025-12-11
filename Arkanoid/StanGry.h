#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <iostream>

#include "Paletka.h"
#include "Pilka.h"
#include "Cegla.h"
#include "BlockData.h"


class StanGry
{
public:
	StanGry(const Paletka& paletka, const Pilka& pilka, const std::vector<Cegla>& blokiWek, int zyciaGry, int punkty);
	void capture(const Paletka& paletka, const Pilka& pilka, const std::vector<Cegla>& blokiWek, int zyciaGry, int punkty);
	bool saveToFile(const std::string& filename) const;
	bool loadFromFile(const std::string& filename);
	void apply(Paletka& paletka, Pilka& pilka, Bloki& nbloki, int& zyciaGry, int& punkty) const;

	const sf::Vector2f& getPaletkaPos() const { return paletkaPos; };
	const sf::Vector2f& getPilkaPos() const { return pilkaPos; };
	const sf::Vector2f& getPilkaVel() const { return pilkaVel; };
	const std::vector<BlockData>& getBloki() const { return bloki; };
	//int getZyciaGracza() const { return zyciaGracza; };


private:
	sf::Vector2f pilkaPos;
	sf::Vector2f paletkaPos;
	sf::Vector2f pilkaVel;
	std::vector<BlockData> bloki;
	int zyciaGracza;
	int wynikGry;
};

StanGry::StanGry(const Paletka& paletka, const Pilka& pilka, const std::vector<Cegla>& blokiWek, int zyciaGry, int punkty)
{
	capture(paletka, pilka, blokiWek, zyciaGry, punkty);
};

void StanGry::capture(const Paletka& paletka, const Pilka& pilka, const std::vector<Cegla>& blokiWek, int zyciaGry, int punkty)
{
	paletkaPos = paletka.getPos();
	pilkaPos = pilka.getPos();
	pilkaVel = pilka.getVelocity();
	zyciaGracza = zyciaGry;
	wynikGry = punkty;

	bloki.clear();
	bloki.reserve(blokiWek.size());

	for (const auto& blk : blokiWek)
	{
		BlockData bd;
		bd.x = blk.getPos().x;
		bd.y = blk.getPos().y;
		bd.hp = blk.getHP();
		bloki.push_back(bd);
	}
}

bool StanGry::saveToFile(const std::string& filename) const
{
	std::ofstream file(filename);

	if (!file.is_open())
		return false;
	file << "PALETKA " << paletkaPos.x << " " << paletkaPos.y << "\n";
	file << "PILKA " << pilkaPos.x << " " << pilkaPos.y << " " << pilkaVel.x << " " << pilkaVel.y << "\n";
	file << "LICZBA_ZYC " << zyciaGracza << "\n";
	file << "LICZBA_PUNKTOW " << wynikGry << "\n";
	file << "LICZBA_BLOKOW " << bloki.size() << "\n";


	for (const auto& b : bloki)
	{
		file << b.x << " " << b.y << " " << b.hp << "\n";
	}

	return true;
}

bool StanGry::loadFromFile(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		return false;
	}

	std::string znacznik;
	int licznikBlokow = 0;

	file >> znacznik >> paletkaPos.x >> paletkaPos.y;
	file >> znacznik >> pilkaPos.x >> pilkaPos.y >> pilkaVel.x >> pilkaVel.y;
	file >> znacznik >> zyciaGracza;
	file >> znacznik >> wynikGry;
	file >> znacznik >> licznikBlokow;

	bloki.clear();

	for (int i = 0; i < licznikBlokow; i++)
	{
		BlockData bd;
		file >> bd.x >> bd.y >> bd.hp;
		bloki.push_back(bd);
	}

	return true;
}

void StanGry::apply(Paletka& paletka, Pilka& pilka, Bloki& nbloki, int& zyciaGry, int& punkty) const
{
	paletka.setPos(paletkaPos);
	pilka.setPos(pilkaPos);
	pilka.setVelocity(pilkaVel);

	nbloki.odbuduj(bloki, 800.f, 600.f);

	zyciaGry = zyciaGracza;
	punkty = wynikGry;
}

