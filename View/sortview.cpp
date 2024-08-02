#include "sortview.h"

void SortView::render(Model *model, std::string& title) {
    SortModel* sortmodel = dynamic_cast<SortModel*>(model);
    int size = sortmodel->getSize();

    window.clear();

    sf::Font font;
    if (!font.loadFromFile("../arial/ARIALI.TTF"))
        return;
    sf::Text text(title, font, 50);
    window.draw(text);

    for (int i = 0; i < size; i++) {
        sf::RectangleShape rect(
            sf::Vector2f(width / size - 2, 
                        -sortmodel->getData(i) * (height / size) - 1));
        rect.setPosition(i * (static_cast<float>(width) / size), 720);
        rect.setFillColor(sortmodel->getColor(i));
        window.draw(rect);
    }
    
    window.display();
}
