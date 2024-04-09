#include "Crossroad.h"

Crossroad::Crossroad(const char &val) : value(val) {}

char Crossroad::getValue() const {
    return value;
}

int Crossroad::getDistance() const {
    return distance;
}

auto Crossroad::getParent() const {
    return parent;
}

void Crossroad::setDistance(int newDistance) {
    distance = newDistance;
}

void Crossroad::setParent(Crossroad *newParent) {
    parent = newParent;
}

Crossroad::~Crossroad() = default;

