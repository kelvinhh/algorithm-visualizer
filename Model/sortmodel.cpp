#include "sortmodel.h"

void SortModel::shuffle() {
    std::shuffle(data.begin(), data.end(), g);
}

void SortModel::sort() {
    for (int i = 0; i < size; i++) {
        int idx = i;
        setColor(i, sf::Color::White);
        for (int j = i + 1; j < size; j++) {
            int pre = idx;
            setColor(j, sf::Color::White);
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            if (data[j] < data[idx])
                idx = j;
            if (pre != idx && pre != i) setColor(pre, sf::Color::Green);
            else if (idx != j) setColor(j, sf::Color::Green);
        }
        if (idx != i) std::swap(data[i], data[idx]);
        setColor(i, sf::Color::Green);
        setColor(idx, sf::Color::Green);
    }
    running = false;
}