#include "model.h"

int Model::getData(int i) const {
    return data[i];
}

int Model::getSize() const {
    return size;
}

sf::Color Model::getColor(int i) const {
    return colors[i];
}