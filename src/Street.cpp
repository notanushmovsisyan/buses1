#include "Street.h"

Street::Street(Crossroad *src, Crossroad *dest, int dur) : source(src), destination(dest), duration(dur) {}

Crossroad *Street::getSource() const {
    return source;
}

Crossroad *Street::getDestination() const {
    return destination;
}
int Street::getDuration() const {
    return duration;
}

void Street::setDuration(int newDuration) {
    duration = newDuration;
}

bool Street::operator==(const Street &other) {
    return source == other.source && destination == other.destination && duration == other.duration;
}
