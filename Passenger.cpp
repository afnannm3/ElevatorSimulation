#include "Passenger.h"

Passenger::Passenger(int passengerID, int startFloor, int destinationFloor, QObject* parent)
    : QObject(parent), passengerID(passengerID), currentFloor(startFloor), destinationFloor(destinationFloor),
      elevatorRequestMade(false) {}  // ✅ Correctly initialized

void Passenger::requestElevator(int direction) {
    if (!elevatorRequestMade) {  // ✅ Prevent multiple requests
        emit elevatorRequested(currentFloor, direction);
        elevatorRequestMade = true;  // ✅ Track that this passenger has requested an elevator
    }
}

void Passenger::pressFloorButton(int floor) {
    destinationFloor = floor;
}

void Passenger::pressHelpButton() {
    emit helpButtonPressed();
}

// ✅ Renamed methods to match the new variable name
bool Passenger::hasRequestedElevator() const {
    return elevatorRequestMade;
}

void Passenger::markElevatorRequested() {
    elevatorRequestMade = true;
}

int Passenger::getStartFloor() const {
    return currentFloor;
}

int Passenger::getDestinationFloor() const {
    return destinationFloor;
}


int Passenger::getID() const {
    return passengerID;
}

//new

void Passenger::boardElevator(int elevatorID) {
    // Mark passenger as on board
    onElevator = true;

    // Immediately request the elevator to go to the passenger’s destination
    emit carRequest(elevatorID, destinationFloor);
}


bool Passenger::isOnElevator() const {
    return onElevator;
}


bool Passenger::isFinished() const {
    return finished;
}

void Passenger::markFinished() {
    finished = true;
}




