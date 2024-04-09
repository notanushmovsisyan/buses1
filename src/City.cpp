#include "City.h"

Crossroad* City::getCrossroad(const char &data) {
    auto crossroadIt = crossroads.find(data);
    if (crossroadIt != crossroads.end()) {
        return crossroadIt->second;
    }
    return nullptr;
}

void City::floydWarshall() {
    shortestPaths = city;
    for (int k = 0; k < numberOfCrossroads; k++) {
        for (int i = 0; i < numberOfCrossroads; i++) {
            if (shortestPaths[i][k] != INT_MAX) {
                for (int j = 0; j < numberOfCrossroads; j++) {
                    if (shortestPaths[k][j] != INT_MAX) {
                        shortestPaths[i][j] = std::min(shortestPaths[i][j], shortestPaths[i][k] + shortestPaths[k][j]);
                    }
                }
            }
        }
    }
}

void City::updateShortestPaths(int i, int j) {
    int duration = city[i][j];
    for (int m = 0; m < numberOfCrossroads; ++m) {
        for (int n = 0; n < numberOfCrossroads; ++n) {
            if (shortestPaths[m][i] == INT_MAX || shortestPaths[j][n] == INT_MAX)
                continue;

            shortestPaths[m][n] = std::min(shortestPaths[m][n], shortestPaths[m][i] + duration + shortestPaths[j][n]);
            shortestPaths[n][m] = std::min(shortestPaths[n][m], shortestPaths[n][j] + duration + shortestPaths[i][m]);
        }
    }
}

char City::intToChar(int i) {
    return (char) i + 'A';
}

int City::charToInt(char c) {
    return (int) c - 65;
}

City::City(int numOfCrossroads)
: numberOfCrossroads(numOfCrossroads),
  city(numberOfCrossroads,std::vector<int>(numberOfCrossroads, INT_MAX)),
  shortestPaths(numberOfCrossroads,std::vector<int>(numberOfCrossroads, INT_MAX)){
    for (int i = 0; i < numberOfCrossroads; ++i) {
        city[i][i] = 0;
        shortestPaths[i][i] = 0;
        char value = (char)(i + 65);
        Crossroad* newCrossroad = new Crossroad(value);
        crossroads[value] = newCrossroad;
        crossroadToStreets[newCrossroad] = std::unordered_set<Street *>();
    }
}

bool City::addStreets(std::vector<std::pair<char, char> > crossroadValues, std::vector<int> durations) {
    if (crossroadValues.size() != durations.size()) {
        return false;
    }

    for(int i = 0; i < crossroadValues.size(); ++i) {
        Crossroad *source = getCrossroad(crossroadValues[i].first);
        Crossroad *destination = getCrossroad(crossroadValues[i].second);

        if (source == nullptr || destination == nullptr) {
            return false;
        }

        Street *newStreet = new Street(source, destination, durations[i]);

        int m = charToInt(source->getValue());
        int n = charToInt(destination->getValue());
        city[m][n] = newStreet->getDuration();
        city[n][m] = newStreet->getDuration();
        shortestPaths[m][n] = newStreet->getDuration();
        shortestPaths[n][m] = newStreet->getDuration();

        if (crossroadToStreets.find(source) == crossroadToStreets.end()
            || crossroadToStreets.find(destination) == crossroadToStreets.end()) {
            return false;
        }

        crossroadToStreets[source].insert(newStreet);
        crossroadToStreets[destination].insert(newStreet);
    }

    for (auto it : crossroadToStreets) {
        for (auto itStreet : it.second) {
            std::cout << itStreet->getSource()->getValue() << " " << itStreet->getDestination()->getValue() << " "
            << itStreet->getDuration() << std::endl;
        }
    }

    floydWarshall();

    return true;
}

int City::addBus(const char &source, const char &destination) {
    int i = source - 65;
    int j = destination - 65;

    if((i >= numberOfCrossroads || j >= numberOfCrossroads) || shortestPaths[i][j] == INT_MAX ) {
        std::string message = "There is no path between " + std::string(1 ,source) + " and "
                              + std::string(1,destination) + ". A bus can't be added.";
        throw std::invalid_argument(message);
    }

    Crossroad *first = getCrossroad(source);
    Crossroad *second = getCrossroad(destination);

    //probably not out_of_range
    if (first == nullptr || second == nullptr) {
        throw std::out_of_range("Attempting to access invalid crossroad");
    }

    std::string id = std::to_string(source) + std::to_string(destination);

    if(busIDs.find(id) != busIDs.end()) {
        return shortestPaths[i][j];
    }

    busIDs.insert(id);
    Bus *newBus = new Bus(first, second);
    indexToBus.push_back(newBus);
    newBus->setDuration(shortestPaths[i][j]);

    return newBus->getDuration();
}

std::vector<Bus *> City::constructStreet(const char &source, const char &destination, int duration) {
    int i = charToInt(source);
    int j = charToInt(destination);

    if((i >= numberOfCrossroads || j >= numberOfCrossroads)  || i == j || city[i][j] != INT_MAX) {
        std::string message = "Either there is already a street between " + std::string(1 ,source) + " and "
                              + std::string(1,destination) + " or these crossroads don't exist";
        throw std::invalid_argument(message);
    }

    Crossroad* first = getCrossroad(source);
    Crossroad* second = getCrossroad(destination);

    if (first == nullptr || second == nullptr) {
        throw std::out_of_range("Attempting to access invalid crossroad");
    }

    Street* newStreet = new Street(first, second, duration);

    if (city[i][j] != INT_MAX && city[j][i] != INT_MAX) {
        throw std::invalid_argument("Street already exists");
    }

    city[i][j] = duration;
    city[j][i] = duration;
    crossroadToStreets[first].insert(newStreet);
    crossroadToStreets[second].insert(newStreet);

    if (shortestPaths[i][j] > duration) {
        updateShortestPaths(i, j);

        for (Bus* current : indexToBus) {
            int m = charToInt(current->getSource()->getValue());
            int n = charToInt(current->getDestination()->getValue());

            if(current->getDuration() > shortestPaths[m][n]) {
                current->setDuration(shortestPaths[m][n]);
            }
        }
    }

    return indexToBus;
}

//std::vector<std::vector<char> > City::details(int busIndex) {}

void City::printCity() {
    std::cout << "City:" << std::endl;
    for(int i = 0; i < numberOfCrossroads; ++i) {
        for(int j = 0; j < numberOfCrossroads; ++j) {
            std::cout << city[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void City::printShortestPaths() {
    std::cout << "Shortest Paths:" << std::endl;
    for(int i = 0; i < numberOfCrossroads; ++i) {
        for(int j = 0; j < numberOfCrossroads; ++j) {
            std::cout << shortestPaths[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void City::printBuses() {
    for (const auto& busPtr : indexToBus) {
        const Bus& bus = *busPtr;
        std::cout << "Bus: " << bus.getSource()->getValue() << " to " << bus.getDestination()->getValue() << ", Duration: " << bus.getDuration() << std::endl;
    }
    std::cout << std::endl;
}
