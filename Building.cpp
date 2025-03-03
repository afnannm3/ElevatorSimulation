#include "Building.h"

Building::Building(int numFloors, int numElevators, QObject* parent) 
    : QObject(parent), numFloors(numFloors), numElevators(numElevators) {}

void Building::addFloor(Floor* floor) {
    floors.append(floor);
}

void Building::addElevator(Elevator* elevator) {
    elevators.append(elevator);
}

int Building::getNumFloors() const {
    return numFloors;
}

int Building::getNumElevators() const {
    return numElevators;
}

QVector<Floor*> Building::getFloors() const {
    return floors;
}

QVector<Elevator*> Building::getElevators() const {
    return elevators;
}
