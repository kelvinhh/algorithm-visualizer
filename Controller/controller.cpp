#include "controller.h"

void Controller::viewRender()  { 
    view->render(model, title); 
}

void Controller::handleEvent() {
    sf::RenderWindow& window = view->getWindow();
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) 
            window.close();
        else if(event.type == sf::Event::KeyPressed) {
            switch(event.key.code) {
                case sf::Keyboard::Space:
                    if (mode)
                        model->start(mode);
                    std::cout << "Haven't choose any sorting algorithm" << std::endl;
                    break;
                case sf::Keyboard::Num1:
                    mode = 1;
                    title = "Selection Sort";
                    break;
                case sf::Keyboard::Num2:
                    mode = 2;
                    title = "Bubble Sort";
                    break;
                case sf::Keyboard::Num3:
                    mode = 3;
                    title = "Insertion Sort";
                    break;
                case sf::Keyboard::Num4:
                    mode = 4;
                    title = "Merge Sort";
                    break;
                case sf::Keyboard::Num5:
                    mode = 5;
                    title = "Quick Sort";
                    break;
                case sf::Keyboard::Num6:
                    mode = 6;
                    title = "Heap Sort";
                    break;
                case sf::Keyboard::Num7:
                    mode = 7;
                    title = "Counting Sort";
                    break;
                case sf::Keyboard::Num8:
                    mode = 8;
                    title = "Radix Sort";
                    break;
                case sf::Keyboard::Num9:
                    mode = 9;
                    title = "Bucket Sort";
                    break;
                case sf::Keyboard::Num0:
                    mode = 10;
                    title = "Shell Sort";
                    break;
                case sf::Keyboard::R:
                    model->shuffle();
                    break;
                case sf::Keyboard::Q:
                    window.close();
                    break;
                default: break;
            }
        }
    }
}
