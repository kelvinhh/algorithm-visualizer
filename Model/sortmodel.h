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

    void wait();
    
    void selectionSort();
    void BubbleSort();
    void InsertionSort();
    void MergeSort(int l, int r);
    void merge(int l, int r, int mid);
    void QuickSort();
    void quicksort(int l, int r);
    void HeapSort();
    void heapify(int n, int i);
    void CountingSort();
    void RadixSort();
    void BucketSort();
    void ShellSort();
};

#endif