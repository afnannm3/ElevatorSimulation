#include "Floor.h"

Floor::Floor(int floorNumber, QObject* parent) 
    : QObject(parent), floorNumber(floorNumber), upButtonPressed(false), downButtonPressed(false) {}

void Floor::pressUpButton() {
    upButtonPressed = true;
    emit requestElevator(floorNumber, 1);
}

void Floor::pressDownButton() {
    downButtonPressed = true;
    emit requestElevator(floorNumber, -1);
}

int Floor::getFloorNumber() const {
    return floorNumber;
}

