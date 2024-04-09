#ifndef BUSES_1_CROSSROAD_H
#define BUSES_1_CROSSROAD_H

#include <climits>

class Crossroad {
private:
    char value;
    Crossroad *parent = nullptr;
    int distance = INT_MAX;

public:
    Crossroad(const char &val);
    char getValue() const;
    int getDistance() const;
    auto getParent() const;
    void setDistance(int newDistance);
    void setParent(Crossroad *newParent);
    ~Crossroad();
};

#endif //BUSES_1_CROSSROAD_H