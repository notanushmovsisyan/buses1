#ifndef UNTITLED_BUS_H
#define UNTITLED_BUS_H

#include "Crossroad.h"

class Bus {
private:
    Crossroad *source;
    Crossroad *destination;
    int duration;

public:
    Bus(Crossroad *src, Crossroad *dest);
    Crossroad *getSource() const;
    Crossroad *getDestination() const;
    int getDuration() const;
    void setDuration(int newDuration);
};

#endif //UNTITLED_BUS_H
