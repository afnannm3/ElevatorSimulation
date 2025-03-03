#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QTimer>

class Elevator : public QObject {
    Q_OBJECT

public:
    explicit Elevator(int elevatorID, int currentFloor, QObject* parent = nullptr);

    // Called by the control system to add a new floor request to the queue
    void moveToFloor(int destinationFloor);
    void openDoor();
    void closeDoor();
    void ringBell();
    void handleHelpButton();
    void handleOverload();

    int getCurrentFloor() const;
    QString getState() const;

    // We'll expose this so we can see if the elevator is truly done or not
    bool hasPendingDestinations() const;

signals:
    void updateElevatorState(int elevatorID, int currentFloor, QString state);
    void playAudioWarning(QString message);

private:
    int elevatorID;
    int currentFloor;
    QString state;  // "idle" or "moving"
    QString doorState; // "open" or "closed"

    QVector<int> destinationFloors;
    QTimer* movementTimer;

    QVector<int> destinationQueue;  // All floors we still need to visit

};

#endif // ELEVATOR_H


