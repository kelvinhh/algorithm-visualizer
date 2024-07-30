#ifndef MODEL_H
#define MODEL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

class Model {
protected:
    std::random_device rd;
    std::mt19937 g;

    int size;
    std::vector<int> data;
    std::vector<sf::Color> colors;

public:
    Model(): g{rd()} {}
    virtual ~Model() = default;
    
    virtual void shuffle() = 0;
    virtual void sort() = 0;

    int getSize() const;
    int getData(int i) const;
    sf::Color getColor(int i) const;
};

#endif