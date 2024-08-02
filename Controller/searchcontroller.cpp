#include "searchcontroller.h"

void SearchController::handleEvent() {
    sf::RenderWindow& window = view->getWindow();
    sf::Event event;
    SearchModel* searchmodel = dynamic_cast<SearchModel*>(model);
    
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) 
            window.close();
        else if(event.type == sf::Event::KeyPressed) {
            switch(event.key.code) {
                case sf::Keyboard::Space:
                    searchmodel->start(0);
                    break;
                case sf::Keyboard::Q:
                    window.close();
                    break;
                default: break;
            }
        }
    }
}