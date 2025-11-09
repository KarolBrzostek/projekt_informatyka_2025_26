#include <SFML/Graphics.hpp>
#include <iostream>
#include "Paletka.h"
#include "Pilka.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800,600 }), "Gra v0.001");
    Paletka pal1({ 400,500 }, { 80,10 }, { 100,0 });
    Pilka pilka1({ 400,300 }, 10.f, { 100,100 });
    window.setFramerateLimit(60);
    sf::Clock deltaClk;
    sf::Time(czas);

    while (window.isOpen())
    {
        czas = deltaClk.restart();
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
		  }
        //aktualizacja
        pal1.ruch(czas, { 800.f,600.f });
        pilka1.ruch(czas, { 800.f,600.f }, pal1);

    window.clear();
    pal1.draw(window);
    pilka1.draw(window);
    window.display();

    }
    return 0;
}

