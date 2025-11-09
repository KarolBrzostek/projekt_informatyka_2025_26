#pragma once

#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "Paletka.h"

class Pilka
{
public:
	Pilka(sf::Vector2f startPos, float radius, sf::Vector2f vel);
	void draw(sf::RenderTarget &window);
	void ruch(sf::Time dt, sf::Vector2f windowWidth, Paletka& pal1);
private:
	sf::Vector2f startPos;
	sf::CircleShape pilka;
	sf::Vector2f velocity{ 300.f,300.f };
	sf::Clock zegarOpoznienia;
	bool opoznienieAktywne = false;
	const float CZAS_OPOZNIENIA = 2.0f;
};

Pilka::Pilka(sf::Vector2f startPos, float radius, sf::Vector2f vel)
{
	velocity = vel;
	pilka.setPosition(startPos);
	pilka.setRadius(radius);
	pilka.setFillColor(sf::Color::Blue);
	pilka.setOrigin(sf::Vector2f({ radius, radius }));
}

void Pilka::draw(sf::RenderTarget &window)
{
	window.draw(pilka);
}


void Pilka::ruch(sf::Time dt, sf::Vector2f windowWidth, Paletka& pal1)
{
	if (opoznienieAktywne)
	{
		if (zegarOpoznienia.getElapsedTime().asSeconds() >= CZAS_OPOZNIENIA)
		{
			pilka.setPosition({400,300});
			velocity.x = 100.f;
			velocity.y = 100.f;
			opoznienieAktywne = false;
		}
		else { return; }
	}

	pilka.move(sf::Vector2f({ velocity.x * dt.asSeconds(),velocity.y * dt.asSeconds() }));

	if (pilka.getPosition().x - pilka.getRadius() < 0 || pilka.getPosition().x + pilka.getRadius() > windowWidth.x)
	{
		velocity.x = -velocity.x;
	}
	if (pilka.getPosition().y - pilka.getRadius() < 0)
	{
		velocity.y = -velocity.y;
	}
	//kolizja z paletka

	sf::FloatRect granicePaletki = pal1.getBounds();
	sf::FloatRect granicePilki = pilka.getGlobalBounds();

	if (granicePilki.findIntersection(granicePaletki))
	{
		velocity.y = -velocity.y;
	}

	if (pilka.getPosition().y + pilka.getRadius() > windowWidth.y)
	{
		velocity.x = 0;
		velocity.y = 0;

		zegarOpoznienia.restart();
		opoznienieAktywne = true;
	}
}