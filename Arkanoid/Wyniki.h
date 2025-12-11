#pragma once


#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

class Wyniki
{
public:
	Wyniki();

	void dodajWynik(int wynik);
	bool saveToFile(const std::string& filename) const;
	bool loadFromFile(const std::string& filename);
	void draw(sf::RenderTarget& window);
	const std::vector<int>& getLista() const { return lista; };

private:
	std::vector<int> lista;
	sf::Font font;
	sf::Text tekst;
};

Wyniki::Wyniki()
{
	font.loadFromFile("arial.ttf");
	tekst.setFont(font);
	tekst.setCharacterSize(28);
	tekst.setFillColor(sf::Color::White);
	tekst.setStyle(sf::Text::Bold);

	loadFromFile("wyniki.txt");
}

void Wyniki::dodajWynik(int wynik)
{
	lista.push_back(wynik);

	std::sort(lista.begin(), lista.end(), std::greater<int>());

	if (lista.size() > 10)
	{
		lista.resize(10);
	}

	saveToFile("wyniki.txt");
}

bool Wyniki::saveToFile(const std::string& filename) const
{
	std::ofstream file(filename);

	if (!file.is_open())
	{
		return false;
	}

	for (int w : lista)
	{
		file << w << "\n";
	}
	return true;
}

bool Wyniki::loadFromFile(const std::string& filename)
{
	std::ifstream file(filename);

	if (!file.is_open())
	{
		return false;
	}

	lista.clear();

	int w;
	while (file >> w)
	{
		lista.push_back(w);
	}

	std::sort(lista.begin(), lista.end(), std::greater<int>());
	if (lista.size() > 10)
	{
		lista.resize(10);
	}

	return true;
}

void Wyniki::draw(sf::RenderTarget& window)
{
	sf::Text tytul;
	tytul.setFont(font);
	tytul.setString("Najlepsze wyniki");
	tytul.setCharacterSize(40);
	tytul.setFillColor(sf::Color::White);
	tytul.setStyle(sf::Text::Bold);
	tytul.setPosition(250.f, 40.f);

	window.draw(tytul);

	float y = 140.f;

	for (int i = 0; i < lista.size(); i++)
	{
		tekst.setString(std::to_string(i + 1) + ".    " + std::to_string(lista[i]));
		tekst.setPosition(240.f, y + i * 40.f);
		window.draw(tekst);
	}

	sf::Text powrot;
	powrot.setFont(font);
	powrot.setCharacterSize(22);
	powrot.setStyle(sf::Text::Bold);
	powrot.setFillColor(sf::Color::White);
	powrot.setString("ESC - powrot do menu.");
	powrot.setPosition(20.f, 540.f);

	window.draw(powrot);
}