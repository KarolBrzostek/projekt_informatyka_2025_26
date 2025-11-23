#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>


#include "paletka.h"
#include "pilka.h"
#include "cegla.h"
#include "bloki.h"

int main()
{
    const int SZEROKOSC = 800;
    const int WYSOKOSC = 600;
    sf::RenderWindow window(sf::VideoMode({ SZEROKOSC,WYSOKOSC }), "Gra v0.01");
    window.setFramerateLimit(60);
    sf::Clock deltaClk;
    sf::Time(czas);

    //tworzenie obiektow
    Paletka pal1({ SZEROKOSC / 2.f,WYSOKOSC - 100.f }, { 80,10 }, { 100,0 });
    Pilka pilka1({ SZEROKOSC / 2.f,WYSOKOSC - 200.f }, 10.f, { 100,100 });


    const int LICZBA_KOLUMN = 12;
    const int LICZBA_WIERSZY = 4;
    float ROZMIAR_BLOKU_X = (SZEROKOSC - (LICZBA_KOLUMN - 1) * 2.f) / LICZBA_KOLUMN;  //uzaleznienie od szerokosci ekranu
    float  ROZMIAR_BLOKU_Y = 20.f;

    ////rysowanie blokow
    Bloki bloki(LICZBA_KOLUMN, LICZBA_WIERSZY, SZEROKOSC, WYSOKOSC);



    while (window.isOpen())
    {
        czas = deltaClk.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //aktualizacja
        pal1.ruch(czas, { 800.f,600.f });
        pilka1.ruch(czas, { 800.f,600.f }, pal1, { SZEROKOSC / 2.f,WYSOKOSC - 200.f });

        //kolizje pilki z blokami
        bloki.sprawdzKolizje(pilka1);

        //usuwanie zniszczonych blokow
        bloki.usunZniszczoneBloki();


        window.clear();
        pal1.draw(window);
        pilka1.draw(window);

        //rysowanie blokow
        bloki.rysujBloki(window);

        window.display();

    }
    return 0;
}

