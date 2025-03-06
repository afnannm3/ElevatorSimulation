#ifndef CONTROLSYSTEM_H
#define CONTROLSYSTEM_H

#include <QObject>
#include <QVector>
#include <QQueue>
#include <QPair>
#include <QMap>
#include <QTimer>
#include "Elevator.h"
#include "Floor.h"
#include "SafetyEvent.h"

class ControlSystem : public QObject {
    Q_OBJECT

public:
    explicit ControlSystem(int numElevators, int numFloors, QObject* parent = nullptr);

    void handleFloorRequest(int floor, int direction);
    void handleCarRequest(int elevatorID, int destination);
    void handleSafetyEvent(SafetyEvent* event);

    QVector<Elevator*> getElevators() const;
    QVector<Floor*> getFloors() const;


    bool isFireActive() const;

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

    // Timers for active "Help" alarms. Key = elevatorID, Value = pointer to QTimer.
    // When the "Help" alarm is triggered, we start a 5-second timer. If it times out,
    // we call 911.
    QMap<int, QTimer*> helpTimers;

    void checkPendingRequests();

    static const int SAFE_FLOOR = 1;


      bool fireActive;
};

#endif // CONTROLSYSTEM_H



