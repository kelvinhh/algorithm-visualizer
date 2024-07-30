#include <SFML/Graphics.hpp>

#include <stdlib.h>
#include <iostream>
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "window");
    

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // draw start

        // draw end

        window.display();
    }

    return EXIT_SUCCESS;
}