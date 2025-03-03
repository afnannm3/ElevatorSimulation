#ifndef BUILDING_H
#define BUILDING_H

#include <QObject>
#include <QVector>
#include "Floor.h"
#include "Elevator.h"

class Building : public QObject {
    Q_OBJECT

public:
    explicit Building(int numFloors, int numElevators, QObject* parent = nullptr);

    void addFloor(Floor* floor);
    void addElevator(Elevator* elevator);

    int getNumFloors() const;
    int getNumElevators() const;
    QVector<Floor*> getFloors() const;
    QVector<Elevator*> getElevators() const;

private:
    int numFloors;
    int numElevators;
    QVector<Floor*> floors;
    QVector<Elevator*> elevators;
};

#endif // BUILDING_H



