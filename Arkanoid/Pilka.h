#pragma once

#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "Paletka.h"

class Pilka
{
public:
	Pilka(sf::Vector2f startPos, float radius, sf::Vector2f vel);
	void draw(sf::RenderTarget& window);
	void ruch(sf::Time dt, sf::Vector2f windowWidth, Paletka& pal1, sf::Vector2f startPos);
	void odbijX();
	void odbijY();
	sf::FloatRect getBounds() const;
	sf::Vector2f getPos() const { return pilka.getPosition(); };
	sf::Vector2f getVelocity() const { return velocity; };

	bool pilkaSpadla() { return czySpadla; };
	void setCzySpadla() { czySpadla = false; };
	void setPos(sf::Vector2f p) { pilka.setPosition(p); };
	void setVelocity(sf::Vector2f v) { velocity = v; };

	void opoznienieRuchu();

private:
	sf::Vector2f startPos;
	sf::CircleShape pilka;
	sf::Vector2f velocity{ 300.f,300.f };
	bool czySpadla = false;

	bool poczatekOpoznienia = false;
	sf::Clock zegarOpoznienia;
	float czasOpoznienia = 1.0f;

	bool widoczny = true;
	sf::Clock zegarMigania;
	float czestotliwoscMigania = 0.15f;
};

Pilka::Pilka(sf::Vector2f startPos, float radius, sf::Vector2f vel)
{
	velocity = vel;
	pilka.setPosition(startPos);
	pilka.setRadius(radius);
	pilka.setFillColor(sf::Color::Blue);
	pilka.setOrigin(sf::Vector2f({ radius, radius }));
}

void Pilka::draw(sf::RenderTarget& window)
{
	if (widoczny)
	{
		window.draw(pilka);
	}

}


void Pilka::ruch(sf::Time dt, sf::Vector2f windowWidth, Paletka& pal1, sf::Vector2f startPos)
{
	if (poczatekOpoznienia)
	{
		if (zegarMigania.getElapsedTime().asSeconds() > czestotliwoscMigania)
		{
			widoczny = !widoczny;
			zegarMigania.restart();
		}

		if (zegarOpoznienia.getElapsedTime().asSeconds() >= czasOpoznienia)
		{
			poczatekOpoznienia = false;
			widoczny = true;
		}
		else
		{
			return;
		}
	}

	pilka.move(sf::Vector2f({ velocity.x * dt.asSeconds(),velocity.y * dt.asSeconds() }));

	if (pilka.getPosition().x - pilka.getRadius() < 0 || pilka.getPosition().x + pilka.getRadius() > windowWidth.x)
	{
		odbijX();
	}
	if (pilka.getPosition().y - pilka.getRadius() < 0)
	{
		odbijY();
	}
	//kolizja z paletka

	sf::FloatRect granicePaletki = pal1.getBounds();
	sf::FloatRect granicePilki = pilka.getGlobalBounds();

	if (granicePilki.intersects(granicePaletki))
	{
		odbijY();
	}

	if (pilka.getPosition().y + pilka.getRadius() > windowWidth.y)
	{
		velocity = { 0.f,0.f };
		czySpadla = true;
	}
}
void Pilka::odbijX()
{
	velocity.x = -velocity.x;
}

void Pilka::odbijY()
{
	velocity.y = -velocity.y;
}

sf::FloatRect Pilka::getBounds() const
{
	return pilka.getGlobalBounds();
}

void Pilka::opoznienieRuchu()
{
	poczatekOpoznienia = true;
	zegarOpoznienia.restart();
}