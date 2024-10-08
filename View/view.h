#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>

#include "model.h"

class View {
   protected:
    const int width, height;
    sf::RenderWindow window;

   public:
    View(int width = 1280, int height = 720, std::string title = "window",
         sf::VideoMode mode = sf::VideoMode(1280, 720))
        : width{width}, height{height}, window(mode, title) {}
    virtual ~View() = default;

    virtual void render(Model* model, std::string& title) = 0;

    sf::RenderWindow& getWindow();
};

#endif
