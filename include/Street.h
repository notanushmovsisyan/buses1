#ifndef BUSES_1_STREET_H
#define BUSES_1_STREET_H

#include "Crossroad.h"

class Street {
private:
    Crossroad *source;
    Crossroad *destination;
    int duration;

public:
    Street(Crossroad *src, Crossroad *dest, int dur);
    Crossroad *getSource() const;
    Crossroad *getDestination() const;
    int getDuration() const;
    void setDuration(int newDuration);
    bool operator==(const Street &other);
};

#endif //BUSES_1_STREET_H
