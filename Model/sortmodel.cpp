#include "sortmodel.h"

void SortModel::shuffle() {
    std::shuffle(data.begin(), data.end(), g);
}

void SortModel::sort() {
    for (int i = 0; i < size; i++) {
        int idx = i;
        for (int j = i + 1; j < size; j++) {
            if (data[j] < data[idx])
                idx = j;
        }
        if (idx != i) std::swap(data[i], data[idx]);
    }
}