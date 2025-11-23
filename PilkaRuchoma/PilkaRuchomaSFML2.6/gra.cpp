#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Gra.h"

enum class GameState
{
	Menu,
	Playing,
	Scores,
	Exiting
};

int main()
{
	const int WYSOKOSC = 600;
	const int SZEROKOSC = 800;

	sf::RenderWindow window(sf::VideoMode(SZEROKOSC, WYSOKOSC), "Arkanoid");
	Menu menu(window.getSize().x, window.getSize().y);

	Gra gra;
	GameState currentstate = GameState::Menu;

	sf::Clock dtClock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (currentstate == GameState::Menu)
			{
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Down)
					{
						menu.przesunD();
					}
					if (event.key.code == sf::Keyboard::Up)
					{
						menu.przesunG();
					}
					if (event.key.code == sf::Keyboard::Enter)
					{
						int selected = menu.getSelectedItem();

						if (selected == 0)
						{
							currentstate = GameState::Playing;
						}
						else if (selected == 1)
						{
							currentstate == GameState::Scores;
						}
						else if (selected==2)
						{
							window.close();
						}
					}
				}
			}
		}

		sf::Time dt = dtClock.restart();

		if (currentstate == GameState::Playing)
		{
			gra.update(dt);
		}

		window.clear();

		if (currentstate == GameState::Menu)
		{
			menu.draw(window);
		}
		else if (currentstate==GameState::Playing)
		{
			gra.render(window);
		}
		else if (currentstate == GameState::Scores)
		{
			//ekran wynikow
		}

		window.display();
	}

}
