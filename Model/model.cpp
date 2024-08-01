#include "model.h"

void Model::stop() {
    if (!running) return;
    running = false;
    if (modelThread.joinable()) modelThread.join();
}
