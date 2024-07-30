#ifndef MODEL_H
#define MODEL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <thread>

class Model {
protected:
    std::random_device rd;
    std::mt19937 g;

    int size;
    std::vector<int> data;
    std::vector<sf::Color> colors;

    std::thread modelThread;
    std::atomic<bool> running{false};

public:
    Model(): g{rd()} {}
    virtual ~Model() { stop(); }
    
    virtual void shuffle() = 0;
    virtual void sort(int i) = 0;

    // setter
    void setColor(int i, sf::Color color);

    // getter
    int getSize() const;
    int getData(int i) const;
    sf::Color getColor(int i) const;

    void start(int i);
    void stop();
};

#endif