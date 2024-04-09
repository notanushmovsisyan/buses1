#include "Bus.h"

Bus::Bus(Crossroad *src, Crossroad *dest) : source(src), destination(dest), duration(0) {}

Crossroad *Bus::getSource() const {
    return source;
}

Crossroad *Bus::getDestination() const {
    return destination;
}

int Bus::getDuration() const {
    return duration;
}

void Bus::setDuration(int newDuration) {
    duration = newDuration;
}
