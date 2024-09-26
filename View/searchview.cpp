#include "searchview.h"

void SearchView::render(Model* model, std::string& title) {
    SearchModel* searchmodel = dynamic_cast<SearchModel*>(model);
    auto v = searchmodel->getSize();
    int M = v[0], N = v[1], grid_size = v[2];

    window.clear();

    for (int x = 0; x < M; x++) {
        for (int y = 0; y < N; y++) {
            sf::RectangleShape rect(sf::Vector2f(grid_size, grid_size));
            rect.setPosition(x * grid_size, y * grid_size);
            rect.setFillColor(searchmodel->getColor(x, y));
            window.draw(rect);
        }
    }

    for (int x = 0; x < M; x++) {
        for (int y = 0; y < N; y++) {
            auto grid = searchmodel->getWall(x, y);

            for (int k = 0; k < 4; k++) {
                if (!grid.ok[k]) {
                    sf::RectangleShape line(sf::Vector2f(grid_size, 5));
                    line.setFillColor(sf::Color(173, 216, 230));

                    if (k == 0) {
                        line.setPosition(x * grid_size, y * grid_size);
                    } else if (k == 1) {
                        line.rotate(90);
                        line.setPosition(x * grid_size, y * grid_size);
                    } else if (k == 2) {
                        line.setPosition(x * grid_size, (y + 1) * grid_size);
                    } else {
                        line.rotate(90);
                        line.setPosition((x + 1) * grid_size, y * grid_size);
                    }

                    window.draw(line);
                }
            }
        }
    }

    // sf::Font font;
    // if (!font.loadFromFile("../arial/ARIALI.TTF"))
    //     return;
    // sf::Text text(title, font, 50);
    // window.draw(text);
    //
    window.display();
}
