#include "Elevator.h"

Elevator::Elevator(int elevatorID, int currentFloor, QObject* parent)
    : QObject(parent), elevatorID(elevatorID), currentFloor(currentFloor),
      state("idle"), doorState("closed") {

    movementTimer = new QTimer(this);
}

//// ================== Replace moveToFloor ==================
void Elevator::moveToFloor(int destinationFloor) {
    // If we're already at the destination, just open the door.
    if (currentFloor == destinationFloor) {
        state = "idle";
        emit updateElevatorState(elevatorID, currentFloor, state);
        ringBell();
        openDoor();
        QTimer::singleShot(3000, this, &Elevator::closeDoor);
        return;
    }

    // Append the new destination if it's not already in the queue.
    if (!destinationFloors.contains(destinationFloor)) {
        destinationFloors.append(destinationFloor);
    }

    // Set the elevator state to moving.
    state = "moving";
    emit updateElevatorState(elevatorID, currentFloor, state);

    // If the movement timer isn't active, start it.
    if (!movementTimer->isActive()) {
        // Use a lambda to drive the floor-by-floor movement.
        connect(movementTimer, &QTimer::timeout, this, [this]() {
            // If no pending destinations, stop the timer.
            if (destinationFloors.isEmpty()) {
                movementTimer->stop();
                state = "idle";
                emit updateElevatorState(elevatorID, currentFloor, state);
                return;
            }

            // Get the next destination in the queue.
            int nextDest = destinationFloors.first();

            // Move one floor at a time toward the next destination.
            if (currentFloor < nextDest) {
                currentFloor++;
            } else if (currentFloor > nextDest) {
                currentFloor--;
            }

            emit updateElevatorState(elevatorID, currentFloor, state);

            // When the next destination is reached:
            if (currentFloor == nextDest) {
                destinationFloors.removeFirst();
                ringBell();
                openDoor();
                // After a 3-second delay, close the door and check for more stops.
                QTimer::singleShot(3000, this, [this]() {
                    closeDoor();
                    if (destinationFloors.isEmpty()) {
                        state = "idle";
                        emit updateElevatorState(elevatorID, currentFloor, state);
                        movementTimer->stop();
                    } else {
                        // Continue moving if there are additional destinations.
                        state = "moving";
                        emit updateElevatorState(elevatorID, currentFloor, state);
                    }
                });
            }
        });
        movementTimer->start(1000); // Move one floor per second.
    }
}




// ================== Door Controls ==================
void Elevator::openDoor() {
    doorState = "open";
    emit updateElevatorState(elevatorID, currentFloor, "Door Open");
}

void Elevator::closeDoor() {
    doorState = "closed";
    emit updateElevatorState(elevatorID, currentFloor, "Door Closed");
}

// ================== Audio and Safety Features ==================
void Elevator::ringBell() {
    emit playAudioWarning("Ding! Elevator arrived.");
}

void Elevator::handleHelpButton() {
    emit playAudioWarning("Emergency Help Button Pressed.");
}

void Elevator::handleOverload() {
    emit playAudioWarning("Overload! Reduce weight.");
}

// ================== Getter Methods ==================
int Elevator::getCurrentFloor() const {
    return currentFloor;
}

QString Elevator::getState() const {
    return state;
}


bool Elevator::hasPendingDestinations() const {
    return !destinationFloors.isEmpty() || (state == "moving");
}
