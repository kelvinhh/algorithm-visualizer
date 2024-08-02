#include "searchcontroller.h"

void SearchController::handleEvent() {
    sf::RenderWindow& window = view->getWindow();
    sf::Event event;
    SearchModel* searchmodel = dynamic_cast<SearchModel*>(model);

    while (window.pollEvent(event)) {
        std::cout << title << std::endl;
        if (event.type == sf::Event::Closed) 
            window.close();
        else if(event.type == sf::Event::KeyPressed) {
            switch(event.key.code) {
                case sf::Keyboard::Space:
                    if (mode)
                        searchmodel->start(mode);
                    break;
                case sf::Keyboard::Num1:
                    mode = 1;
                    title = "dfs generator";
                    break;
                case sf::Keyboard::Num2:
                    mode = 2;
                    title = "prim";
                    break;
                case sf::Keyboard::Num3:
                    mode = 3;
                    title = "wilson";
                    break;
                case sf::Keyboard::Num4:
                    mode = 4;
                    title = "dfs solver";
                    break;
                case sf::Keyboard::Num5:
                    mode = 5;
                    title = "dijkstra";
                    break;
                case sf::Keyboard::Num6:
                    mode = 6;
                    title = "Astar";
                    break;
                case sf::Keyboard::Num7:
                    mode = 7;
                    title = "reset";
                    break;
                case sf::Keyboard::Num8:
                    mode = 8;
                    break;
                case sf::Keyboard::Num9:
                    mode = 9;
                    break;
                 case sf::Keyboard::Num0:
                    mode = 9;
                    break;
                case sf::Keyboard::Q:
                    window.close();
                    break;
                default:
                    break;
            }
        }
    }
}
