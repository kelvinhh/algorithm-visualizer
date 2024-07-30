#include "model.h"

void Model::setColor(int i, sf::Color color) {
    colors[i] = color;
}

int Model::getData(int i) const {
    return data[i];
}

int Model::getSize() const {
    return size;
}

sf::Color Model::getColor(int i) const {
    return colors[i];
}

void Model::start() {
    if (running) return;
    running = true;
    if (modelThread.joinable()) modelThread.join();
    modelThread = std::thread(&Model::sort, this);
}

void Model::stop() {
    running = false;
    if (modelThread.joinable()) modelThread.detach();
}
