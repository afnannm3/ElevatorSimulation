#ifndef PASSENGER_H
#define PASSENGER_H

#include <QObject>

class Passenger : public QObject {
    Q_OBJECT

public:
    explicit Passenger(int passengerID, int startFloor, int destinationFloor, QObject* parent = nullptr);

    void requestElevator(int direction);
    void pressFloorButton(int floor);
    void pressHelpButton();

    int getStartFloor() const;
    int getDestinationFloor() const;

    bool hasRequestedElevator() const;
    void markElevatorRequested();

    int getID() const;


    // Called by MainWindow / simulation code to let the passenger board the elevator
     void boardElevator(int elevatorID);
     // Flags
     bool isOnElevator() const;

     // Track if the passenger has disembarked at their destination.
     bool isFinished() const;
     void markFinished();

     // Get the elevator ID the passenger is on.
     int getBoardedElevatorID() const;




signals:
    void elevatorRequested(int floor, int direction);
    void helpButtonPressed();

    // Inside elevator (car) request
    void carRequest(int elevatorID, int destinationFloor);

private:
    int passengerID;
    int currentFloor;
    int destinationFloor;
    bool elevatorRequestMade;  //  New flag to prevent multiple requests

    bool onElevator;           // Is the passenger already on an elevator?

    bool finished;

    int boardedElevatorID;



};

#endif // PASSENGER_H
