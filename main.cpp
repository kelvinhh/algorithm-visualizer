#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <random>

constexpr int WIDTH = 1280;
constexpr int HEIGHT = 720;

const sf::Color ORI_COL = sf::Color::Green;
const sf::Color SEL_COL = sf::Color::White;

class SortVisualizer {
private:
    std::random_device rd;
    std::mt19937 g;
    sf::RenderWindow& window;

    int size;
    std::vector<int> data;
    std::vector<sf::Color> colors;
public:
    SortVisualizer(sf::RenderWindow& window, int size): g{rd()}, window{window}, size{size} {
        data.resize(size);
        std::iota(data.begin(), data.end(), 1);
        colors.assign(size, ORI_COL);
        shuffle();
    }

    void shuffle() { std::shuffle(data.begin(), data.end(), g); }

    void render() {
        window.clear();
        for (int i = 0; i < size; i++) {
            sf::RectangleShape rect(sf::Vector2f(WIDTH / size - 2, -data[i] * (HEIGHT / size) - 1));
            rect.setPosition(i * (static_cast<float>(WIDTH) / size), 720);
            rect.setFillColor(colors[i]);
            window.draw(rect);
        }
        window.display();
    }

    // O(N^2)
    void selection_sort() {
        for (int i = 0; i < size; i++) {
            int idx = i;
            colors[idx] = SEL_COL;
            for (int j = i + 1; j < size; j++) {
                colors[j] = SEL_COL;
                render();
                if (data[j] < data[idx]) {
                    if (idx != i)
                        colors[idx] = ORI_COL;
                    idx = j;
                } else colors[j] = ORI_COL;
            }
            colors[i] = colors[idx] = ORI_COL;
            if (idx != i) std::swap(data[i], data[idx]);
        }
    }

};

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "window");
    SortVisualizer visualizer = SortVisualizer(window, 100);
    bool stop = false;

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (!stop) {
            visualizer.selection_sort();
        }
        stop = true;

        
        visualizer.render();
    }

    return EXIT_SUCCESS;
}