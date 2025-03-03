#include "Administrator.h"
#include <QDebug>  // For debugging

Administrator::Administrator(const QString& name, QObject* parent) 
    : QObject(parent), name(name), simulationRunning(false) {}

void Administrator::setupSimulation(int numFloors, int numElevators, int numPassengers) {
    // Implementation to configure simulation parameters
    qDebug() << "Setting up simulation with:"
                 << numFloors << "floors,"
                 << numElevators << "elevators,"
                 << numPassengers << "passengers.";
        // Store the values (if needed)
}

void Administrator::startSimulation() {
    simulationRunning = true;
    // Notify the system to start processing
}

void Administrator::pauseSimulation() {
    simulationRunning = false;
    // Pause the simulation logic
}

void Administrator::stopSimulation() {
    simulationRunning = false;
    // Stop simulation execution
}
