#include "Display.h"

Display::Display(QObject* parent) : QObject(parent), currentFloor(1) {}

void Display::updateDisplay(int floor, const QString& warningMessage) {
    currentFloor = floor;
    this->warningMessage = warningMessage;
    emit displayUpdated(floor, warningMessage);
}

QString Display::getWarningMessage() const {
    return warningMessage;
}

