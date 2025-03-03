#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTimer>
#include "Building.h"
#include "ControlSystem.h"
#include "Passenger.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Simulation Control Slots
    void on_startButton_clicked();
    void on_pauseButton_clicked();
    void on_continueButton_clicked();
    void on_stopButton_clicked();

    // Safety Event Slots
    void on_fireButton_clicked();
    void on_powerOutButton_clicked();

    // Elevator Control Slots
    void on_elevator1Help_clicked();
    void on_elevator1DoorObstacle_clicked();
    void on_elevator1Overload_clicked();
    void on_elevator1OpenDoor_clicked();
    void on_elevator1CloseDoor_clicked();
    void on_elevator2Help_clicked();
    void on_elevator2DoorObstacle_clicked();
    void on_elevator2Overload_clicked();
    void on_elevator2OpenDoor_clicked();
    void on_elevator2CloseDoor_clicked();

    // Utility Methods
    void setupPassengers();
    void updateElevatorDisplay();
    void updateLogConsole(QString message);

private:
    Ui::MainWindow *ui;
    Building* building;
    ControlSystem* controlSystem;
    QVector<Passenger*> passengers;
    int simulationStep;
    QTimer* simulationTimer;

    // Helper to see if all passengers/elevators are done
    void checkIfSimulationComplete();
};

#endif // MAINWINDOW_H


