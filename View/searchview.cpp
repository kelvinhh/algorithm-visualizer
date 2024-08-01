#include "searchview.h"

void SearchView::render(Model *model, std::string& title) {
    SearchModel* searchmodel = dynamic_cast<SearchModel*>(model);
    auto v = searchmodel->getSize();
    int M = v[0], N = v[1];

    window.clear();
    for (int x = 0; x < M; x++) {
        for (int y = 0; y < N; y++) {
            sf::RectangleShape rect(sf::Vector2f(40, 40));
            rect.setPosition(x * 40, y * 40);
            rect.setFillColor(searchmodel->getColor(x, y));
            window.draw(rect);
        }
    }

    for (int x = 0; x < M; x++) {
        for (int y = 0; y < N; y++) {
            auto grid = searchmodel->getWall(x, y);
            for (int k = 0; k < 4; k++) {
                if (!grid.ok[k]) {
                    sf::RectangleShape line(sf::Vector2f(40, 5));
                    line.setFillColor(sf::Color(173, 216, 230));

                    if (k == 0) {
                        line.setPosition(x * 40, y * 40);
                    } else if (k == 1) {
                        line.rotate(90);
                        line.setPosition(x * 40, y * 40);
                    } else if (k == 2) {
                        line.setPosition(x * 40, (y + 1) * 40);
                    } else {
                        line.rotate(90);
                        line.setPosition((x + 1) * 40, y * 40);
                    }
                    window.draw(line);
                }
            }
        }
    }
    window.display();
}