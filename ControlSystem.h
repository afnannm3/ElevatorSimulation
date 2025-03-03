#ifndef CONTROLSYSTEM_H
#define CONTROLSYSTEM_H

#include <QObject>
#include <QVector>
#include "Elevator.h"
#include "Floor.h"
#include "SafetyEvent.h"
#include <QQueue>
#include <QPair>

class ControlSystem : public QObject {
    Q_OBJECT

public:
    explicit ControlSystem(int numElevators, int numFloors, QObject* parent = nullptr);

    void handleFloorRequest(int floor, int direction);
    void handleCarRequest(int elevatorID, int destination);
    void handleSafetyEvent(SafetyEvent* event);

    QVector<Elevator*> getElevators() const;
    QVector<Floor*> getFloors() const;

signals:
    void updateSimulationLog(const QString& logMessage);

public slots:
    // We'll define a slot to check pending requests if an elevator became idle
    void onElevatorStateChanged(int elevatorID, int floor, QString state);

private:
    QVector<Elevator*> elevators;
    QVector<Floor*> floors;

    // If we can’t find an idle elevator, we store the request here
        // QPair<int,int> = <floor, direction>
        QQueue<QPair<int,int>> pendingRequests;

        // Helper
        void checkPendingRequests();
};

#endif // CONTROLSYSTEM_H



