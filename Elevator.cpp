#include "Elevator.h"

Elevator::Elevator(int elevatorID, int currentFloor, QObject* parent)
    : QObject(parent), elevatorID(elevatorID), currentFloor(currentFloor),
      state("idle"), doorState("closed"), simulationActive(true) {

    movementTimer = new QTimer(this);
}

void Elevator::activateOverloadMode() {
    overloadActive = true;
    state = "overload";

    // Stop the movement timer so we do not move
    if (movementTimer->isActive()) {
        movementTimer->stop();
    }

    // Possibly open the doors so passengers can unload
    openDoor();

    // Emit an update so that logs show we are now "overload"
    emit updateElevatorState(elevatorID, currentFloor, "OVERLOAD");

    // Present an audio warning
    emit playAudioWarning("Overload! Reduce weight before resuming movement.");
}

void Elevator::overrideDestination(int safeFloor) {
    // Clear all current destinations
    destinationFloors.clear();

    // Add only the safe floor
    destinationFloors.append(safeFloor);

    // If elevator is idle, we switch to moving
    if (state == "idle") {
        state = "moving";
        emit updateElevatorState(elevatorID, currentFloor, state);
    }

    // If the movement timer isn't active, start it
    if (!movementTimer->isActive()) {
        connect(movementTimer, &QTimer::timeout, this, [this]() {
            if (!simulationActive) return;

            if (destinationFloors.isEmpty()) {
                movementTimer->stop();
                state = "idle";
                emit updateElevatorState(elevatorID, currentFloor, state);
                return;
            }

            int nextDest = destinationFloors.first();

            // Move one floor at a time toward the safe floor
            if (currentFloor < nextDest) {
                currentFloor++;
            } else if (currentFloor > nextDest) {
                currentFloor--;
            }

            emit updateElevatorState(elevatorID, currentFloor, state);

            // When we arrive at the safe floor:
            if (currentFloor == nextDest) {
                destinationFloors.removeFirst();
                ringBell();
                openDoor();
                QTimer::singleShot(3000, this, [this]() {
                    if (!simulationActive) return;
                    closeDoor();
                    if (destinationFloors.isEmpty()) {
                        state = "idle";
                        emit updateElevatorState(elevatorID, currentFloor, state);
                        movementTimer->stop();
                    } else {
                        // If for some reason we had more destinations (unlikely in a fire scenario),
                        // we keep moving.
                        state = "moving";
                        emit updateElevatorState(elevatorID, currentFloor, state);
                    }
                });
            }
        });
        movementTimer->start(1000); // 1 floor per second
    }
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
            // If simulation is not active, simply return.

            if (!simulationActive) return;


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
                    if (!simulationActive) return;
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
void Elevator::setSimulationActive(bool active) {
    simulationActive = active;
}
