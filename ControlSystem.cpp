#include "ControlSystem.h"
#include "Floor.h"
#include "SafetyEvent.h"
#include <limits>  // For INT_MAX

ControlSystem::ControlSystem(int numElevators, int numFloors, QObject* parent)
    : QObject(parent)
{
    // Create the elevators
    for (int i = 0; i < numElevators; ++i) {
        Elevator* e = new Elevator(i, 1, this);
        elevators.append(e);

        // Whenever an elevator updates its state, we might re-check pending requests
        connect(e, &Elevator::updateElevatorState,
                this, &ControlSystem::onElevatorStateChanged);
    }

    // Create the floors
    for (int i = 1; i <= numFloors; ++i) {
        floors.append(new Floor(i, this));
    }
}

// ================== Replace handleFloorRequest ==================
void ControlSystem::handleFloorRequest(int floor, int direction) {
    QString dirStr = (direction > 0) ? "up" : "down";
    emit updateSimulationLog(QString("Elevator requested at floor %1, direction: %2")
                             .arg(floor).arg(dirStr));

    // Find an idle elevator
    int bestElevator = -1;
    int bestDistance = INT_MAX;
    for (int i = 0; i < elevators.size(); ++i) {
        if (elevators[i]->getState() == "idle" && !elevators[i]->hasPendingDestinations()) {
            int distance = qAbs(elevators[i]->getCurrentFloor() - floor);
            if (distance < bestDistance) {
                bestDistance = distance;
                bestElevator = i;
            }
        }
    }

    if (bestElevator != -1) {
        emit updateSimulationLog(QString("Assigned Elevator %1 to floor request at %2")
                                 .arg(bestElevator).arg(floor));
        handleCarRequest(bestElevator, floor);
    } else {
        // No idle elevator. Queue the request
        emit updateSimulationLog("No idle elevator available; request queued.");
        pendingRequests.enqueue(qMakePair(floor, direction));
    }
}


// ================== handleCarRequest (No Change) ==================
void ControlSystem::handleCarRequest(int elevatorID, int destination) {
    emit updateSimulationLog(QString("Elevator %1 moving to floor %2")
                             .arg(elevatorID).arg(destination));
    elevators[elevatorID]->moveToFloor(destination);
}

// ================== handleSafetyEvent (No Change) ==================
void ControlSystem::handleSafetyEvent(SafetyEvent* event) {
    emit updateSimulationLog(QString("Safety Event Triggered: %1").arg(event->getEventType()));
}

// ================== Getter Methods (No Change) ==================
QVector<Elevator*> ControlSystem::getElevators() const {
    return elevators;
}

QVector<Floor*> ControlSystem::getFloors() const {
    return floors;
}

// When an elevator changes state, see if it became idle and can service a pending request
void ControlSystem::onElevatorStateChanged(int elevatorID, int floor, QString state) {
    Q_UNUSED(elevatorID)
    Q_UNUSED(floor)

    // If elevator is now "idle", check if we have pending requests to assign
    if (state == "idle") {
        checkPendingRequests();
    }
}

void ControlSystem::checkPendingRequests() {
    // Try to assign each pending request to any idle elevator
    // We do a simple approach: for each request in the queue, see if there's an idle elevator.
    // If found, assign it, remove the request from the queue. Otherwise, keep it.
    QQueue<QPair<int,int>> tempQueue;

    while (!pendingRequests.isEmpty()) {
        auto request = pendingRequests.dequeue();
        int floor = request.first;
        int direction = request.second;
        Q_UNUSED(direction);

        // Try to find an idle elevator for this request
        int bestElevator = -1;
        int bestDistance = INT_MAX;

        for (int i = 0; i < elevators.size(); ++i) {
            if (elevators[i]->getState() == "idle" && !elevators[i]->hasPendingDestinations()) {
                int dist = qAbs(elevators[i]->getCurrentFloor() - floor);
                if (dist < bestDistance) {
                    bestDistance = dist;
                    bestElevator = i;
                }
            }
        }

        if (bestElevator != -1) {
            emit updateSimulationLog(
                QString("Assigned Elevator %1 (from queue) to floor request at %2")
                    .arg(bestElevator).arg(floor));
            handleCarRequest(bestElevator, floor);
        } else {
            // Couldn’t assign – re-queue it
            tempQueue.enqueue(request);
        }
    }

    // Put back unassigned requests
    while (!tempQueue.isEmpty()) {
        pendingRequests.enqueue(tempQueue.dequeue());
    }
}
