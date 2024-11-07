#ifndef WORLD_H
#define WORLD_H
#include "node.h"
#include <vector>

class World {
public:
    std::vector<Node> nodes;

    World() : currentTime(0) {}

    void stepForward(int steps = 1) {
        currentTime += steps;
        // TODO: Handle message passing/receiving in nodes
    }

    void stepBackward(int steps = 1) {
        currentTime -= steps;
        if (currentTime < 0) currentTime = 0;
    }

    void reset() {
        currentTime = 0;
    }

    int getCurrentTime() const {
        return currentTime;
    }

private:
    int currentTime;
};

#endif