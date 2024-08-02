#include "sortmodel.h"

void SortModel::start(int i) {
    if (running) return;
    running = true;
    if (modelThread.joinable()) modelThread.join();
    modelThread = std::thread(&SortModel::sort, this, i);
}

void SortModel::sort(int i) {
    switch (i) {
        case 1:
            selectionSort();
            break;
        case 2: 
            BubbleSort();
            break;
        case 3:
            InsertionSort();
            break;
        case 4: 
            MergeSort(0, size - 1);
            break;
        case 5: 
            QuickSort();
            break;
        case 6:
            HeapSort();
            break;
        case 7: 
            CountingSort();
            break;
        case 8: 
            RadixSort();
            break;
        case 9: 
            BucketSort();
            break;
        case 10: 
            ShellSort();
            break;
        default: break;
    }
    
    if (std::ranges::is_sorted(data))
        std::cout << "completed" << std::endl;
    running = false;
}

void SortModel::shuffle() {
    if (running) return;
    std::shuffle(data.begin(), data.end(), g);
}

void SortModel::wait() {
    std::this_thread::sleep_for(std::chrono::milliseconds(5)); 
}

void SortModel::highlight(const std::vector<int>& pos) {
    for (int x: pos)
        setColor(x, MyColor::azure);
    wait();
    for (int x: pos)
        setColor(x, MyColor::cornflower_blue);
}

void SortModel::selectionSort() {
    std::vector<int> pos;
    for (int i = 0; i < size; i++) {
        int idx = i;
        for (int j = i + 1; j < size; j++) {
            highlight({idx, j});
            if (data[j] < data[idx])
                idx = j;
        }
        if (idx != i) std::swap(data[i], data[idx]);
    }
}

void SortModel::BubbleSort() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            highlight({j, j + 1});
            if (data[j] > data[j + 1]) {
                std::swap(data[j], data[j + 1]);
            }
        }
    }
}

void SortModel::InsertionSort() {
    for (int i = 1; i < size; i++) {
        int key = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > key) {
            highlight({j, j + 1});
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;
    }
}

void SortModel::MergeSort(int l, int r) {
    if (l >= r) return;
    int mid = (l + r) >> 1;
    MergeSort(l, mid);
    MergeSort(mid + 1, r);
    merge(l, mid, r);
}

void SortModel::merge(int l, int mid, int r) {
    int i = l, j = mid + 1, k = 0;
    std::vector<int> temp(r - l + 1);
    while (i <= mid && j <= r) {
        highlight({i, j});
        if (data[i] <= data[j]) {
            temp[k++] = data[i++];
        } else {
            temp[k++] = data[j++];
        }
    }
    while (i <= mid) {
        highlight({i});
        temp[k++] = data[i++];
    }
    while (j <= r) {
        highlight({j});
        temp[k++] = data[j++];
    }
    for (int i = l; i <= r; i++) {
        highlight({i});
        data[i] = temp[i - l];
    }
    wait();
}

void SortModel::QuickSort() {
    quicksort(0, size - 1);
}

void SortModel::quicksort(int l, int r) {
    if (l < r) {
        int pivot = data[r];
        int i = l - 1;
        for (int j = l; j < r; j++) {
            highlight({pivot, j});
            if (data[j] < pivot) {
                i++;
                std::swap(data[i], data[j]);
            }
        }
        highlight({i + 1, r});
        std::swap(data[i + 1], data[r]);
        quicksort(l, i);
        quicksort(i + 2, r);
    }
}

void SortModel::HeapSort() {
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(size, i);
    }
    for (int i = size - 1; i > 0; i--) {
        highlight({0, i});
        std::swap(data[0], data[i]);
        heapify(i, 0);
    }
}

void SortModel::heapify(int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && data[l] > data[largest]) largest = l;
    if (r < n && data[r] > data[largest]) largest = r;
    if (largest != i) {
        highlight({i, largest});
        std::swap(data[i], data[largest]);
        heapify(n, largest);
    }
}

void SortModel::CountingSort() {
    int max = *std::max_element(data.begin(), data.end());
    std::vector<int> count(max + 1);
    std::vector<int> output(size);
    for (int i = 0; i < size; i++) {
        count[data[i]]++;
    }
    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }
    for (int i = size - 1; i >= 0; i--) {
        output[count[data[i]] - 1] = data[i];
        count[data[i]]--;
    }
    for (int i = 0; i < size; i++) {
        data[i] = output[i];
    }
}

void SortModel::RadixSort() {
    int max = *std::max_element(data.begin(), data.end());
    for (int exp = 1; max / exp > 0; exp *= 10) {
        std::vector<int> output(size);
        std::vector<int> count(10);
        for (int i = 0; i < size; i++) {
            count[(data[i] / exp) % 10]++;
        }
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }
        for (int i = size - 1; i >= 0; i--) {
            output[count[(data[i] / exp) % 10] - 1] = data[i];
            count[(data[i] / exp) % 10]--;
        }
        for (int i = 0; i < size; i++) {
            data[i] = output[i];
        }
    }
}

void SortModel::BucketSort() {
    int max = *std::max_element(data.begin(), data.end());
    int min = *std::min_element(data.begin(), data.end());
    int range = max - min;
    int bucketSize = 10;
    int bucketCount = range / bucketSize + 1;
    std::vector<std::vector<int>> buckets(bucketCount);
    for (int i = 0; i < size; i++) {
        int idx = (data[i] - min) / bucketSize;
        buckets[idx].push_back(data[i]);
    }
    for (int i = 0; i < bucketCount; i++) {
        std::sort(buckets[i].begin(), buckets[i].end());
    }
    int idx = 0;
    for (int i = 0; i < bucketCount; i++) {
        for (int j = 0; j < buckets[i].size(); j++) {
            data[idx++] = buckets[i][j];
        }
    }
}

void SortModel::ShellSort() {
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            int temp = data[i];
            int j;
            for (j = i; j >= gap && data[j - gap] > temp; j -= gap) {
                highlight({j, j - gap});
                data[j] = data[j - gap];
            }
            data[j] = temp;
        }
    }
}

void SortModel::setColor(int i, sf::Color color) {
    colors[i] = color;
}

int SortModel::getSize() const {
    return size;
}

int SortModel::getData(int i) const {
    return data[i];
}

sf::Color SortModel::getColor(int i) const {
    return colors[i];
}