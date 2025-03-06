#include "SafetyEvent.h"

SafetyEvent::SafetyEvent(const QString& eventType, int timeStep, int elevatorID, QObject* parent) 
    : QObject(parent), eventType(eventType), timeStep(timeStep), elevatorID(elevatorID) {}

void SafetyEvent::triggerEvent() {
    emit safetyEventTriggered(eventType);
}

void SafetyEvent::resolveEvent() {
    emit safetyEventTriggered(eventType + " Resolved");
}

QString SafetyEvent::getEventType() const {
    return eventType;
}

// Definition for getElevatorID() with the same signature as in the header:
int SafetyEvent::getElevatorID() const {
    return elevatorID;
}
