#include "controller.h"

void Controller::handleEvent() {
    sf::RenderWindow& window = view.getWindow();
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
    }
}