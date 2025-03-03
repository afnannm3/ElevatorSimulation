#ifndef FLOOR_H
#define FLOOR_H

#include <QObject>

class Floor : public QObject {
    Q_OBJECT

public:
    explicit Floor(int floorNumber, QObject* parent = nullptr);

    void pressUpButton();
    void pressDownButton();
    int getFloorNumber() const;

signals:
    void requestElevator(int floor, int direction);

private:
    int floorNumber;
    bool upButtonPressed;
    bool downButtonPressed;
};

#endif // FLOOR_H


