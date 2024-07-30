#ifndef SORTMODEL_H
#define SORTMODEL_H

#include "model.h"

class SortModel: public Model {
public:
    SortModel(int size) {
        this->size = size;
        data.resize(size);
        std::iota(data.begin(), data.end(), 1);
        colors.assign(size, sf::Color::Green);
        shuffle();
    }

    void sort(int i) override;
    void shuffle() override;
    
    void selection_sort();
};

#endif