#include "controller.h"

void Controller::handleEvent() {
    sf::RenderWindow& window = view.getWindow();
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) 
            window.close();
        else if(event.type == sf::Event::KeyPressed)
            if (event.key.code == sf::Keyboard::Space)
                model.start();
            else if (event.key.code == sf::Keyboard::R)
                model.shuffle();
            else if (event.key.code == sf::Keyboard::Q)
                window.close();
    }
}