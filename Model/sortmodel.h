#ifndef SORTMODEL_H
#define SORTMODEL_H

#include "model.h"

class SortModel: public Model {
private:
    int size;
    std::vector<int> data;
    std::vector<sf::Color> colors;

public:
    SortModel(int size) {
        this->size = size;
        data.resize(size);
        std::iota(data.begin(), data.end(), 1);
        colors.assign(size, MyColor::cornflower_blue);
        shuffle();
    }

    void sort(int i);
    void shuffle();
    void start(int i) override;

    void wait();
    void highlight(const std::vector<int>& pos);
    
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

    // setter
    void setColor(int i, sf::Color color);

    // getter
    int getSize() const;
    int getData(int i) const;
    sf::Color getColor(int i) const;
};

#endif