#include "Elevator.h"

Elevator::Elevator(int elevatorID, int currentFloor, QObject* parent)
    : QObject(parent), elevatorID(elevatorID), currentFloor(currentFloor),
      state("idle"), doorState("closed") {

    movementTimer = new QTimer(this);
}

//// ================== Replace moveToFloor ==================
void Elevator::moveToFloor(int destinationFloor) {
    // If the elevator is already there, open the door so passengers can board/exit.
    if (currentFloor == destinationFloor) {
        // Log/update state to "idle" (already arrived)
        state = "idle";
        emit updateElevatorState(elevatorID, currentFloor, state);

        // Sound the bell and open doors
        ringBell();
        openDoor();

        // Close doors automatically after 3s
        QTimer::singleShot(3000, this, &Elevator::closeDoor);
        return;
    }

    state = "moving";
    emit updateElevatorState(elevatorID, currentFloor, state);

    if (!destinationFloors.contains(destinationFloor)) {
        destinationFloors.append(destinationFloor);
    }
    // If the elevator isn’t already moving, start the movement timer
    if (!movementTimer->isActive()) {
        connect(movementTimer, &QTimer::timeout, this, [this]() {
            if (!destinationFloors.isEmpty()) {
                int nextDest = destinationFloors.first();
                if (currentFloor < nextDest) {
                    currentFloor++;
                } else if (currentFloor > nextDest) {
                    currentFloor--;
                }

                emit updateElevatorState(elevatorID, currentFloor, state);

                if (currentFloor == nextDest) {
                    destinationFloors.removeFirst();
                    state = "idle";
                    emit updateElevatorState(elevatorID, currentFloor, state);
                    ringBell();
                    openDoor();

                    QTimer::singleShot(3000, this, &Elevator::closeDoor);

                    if (destinationFloors.isEmpty()) {
                        movementTimer->stop();
                    }
                }
            }
        });

        movementTimer->start(1000); // ✅ Floor-by-floor movement
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
    return !destinationQueue.isEmpty() || (state == "moving");
}
