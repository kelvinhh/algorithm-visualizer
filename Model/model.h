#ifndef MODEL_H
#define MODEL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <thread>
#include <mutex>
#include <iostream>

class Model {
protected:
    std::random_device rd;
    std::mt19937 g;

    std::thread modelThread;
    std::atomic<bool> running{false};

public:
    Model(): g{rd()} { srand(time(NULL)); }
    virtual ~Model() { stop(); }
    
    virtual void start(int i) = 0;
    void stop();
};

#endif