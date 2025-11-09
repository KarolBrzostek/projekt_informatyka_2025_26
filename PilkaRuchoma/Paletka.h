#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Paletka
{
public:
	Paletka(sf::Vector2f startPos, sf::Vector2f rozmiar, sf::Vector2f vel);
	void draw(sf::RenderTarget& window);
	void ruch(sf::Time dt, sf::Vector2f windowWidth);
	sf::FloatRect getBounds() const;
private:
	sf::RectangleShape paletka;
	sf::Vector2f velocity{ 300.f,0.f };
};

Paletka::Paletka(sf::Vector2f startPos, sf::Vector2f rozmiar, sf::Vector2f vel)
{
	velocity = vel;
	paletka.setPosition(startPos);
	paletka.setSize(rozmiar);
	paletka.setOrigin(sf::Vector2f(rozmiar.x / 2.0, rozmiar.y / 2.0));
	paletka.setFillColor(sf::Color::Yellow);
}

void Paletka::draw(sf::RenderTarget& window)
{
	window.draw(paletka);
}

void Paletka::ruch(sf::Time dt, sf::Vector2f windowWidth)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		paletka.move(sf::Vector2f(-velocity.x * 2*dt.asSeconds(), 0));

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		paletka.move(sf::Vector2f(velocity.x * 2*dt.asSeconds(), 0));
	}

	//kolizja ze sciana
	 if (paletka.getPosition().x - paletka.getSize().x / 2 < 0)
		{
			paletka.setPosition(sf::Vector2f(paletka.getSize().x / 2, paletka.getPosition().y));
		}


	 if ((paletka.getPosition().x + paletka.getSize().x / 2) > windowWidth.x)
	 {
		 paletka.setPosition(sf::Vector2f((windowWidth.x-paletka.getSize().x / 2), paletka.getPosition().y));
	 }
}

sf::FloatRect Paletka::getBounds() const
{
	return paletka.getGlobalBounds();
}
