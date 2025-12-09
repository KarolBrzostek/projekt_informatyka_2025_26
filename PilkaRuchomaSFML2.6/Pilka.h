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

private:
	sf::Vector2f startPos;
	sf::CircleShape pilka;
	sf::Vector2f velocity{ 300.f,300.f };
	bool czySpadla = false;
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
	window.draw(pilka);
}


void Pilka::ruch(sf::Time dt, sf::Vector2f windowWidth, Paletka& pal1, sf::Vector2f startPos)
{

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
		velocity.x = 0;
		velocity.y = 0;

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