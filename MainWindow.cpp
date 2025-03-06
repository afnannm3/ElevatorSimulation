#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "ControlSystem.h"
#include "Floor.h"
#include "SafetyEvent.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      building(new Building(5, 2, this)), // Example: 5 floors, 2 elevators
      controlSystem(new ControlSystem(2, 5, this)),
      simulationStep(0),
      simulationRunning(false)
{
    ui->setupUi(this);

    // Initialize simulation timer
    simulationTimer = new QTimer(this);
    connect(simulationTimer, &QTimer::timeout, this, [this]() {
        // Only increment simulation step if simulation is running
        if (!simulationRunning) return;

        simulationStep++;
        ui->simulationStepLabel->setText(QString("Simulation Step: %1").arg(simulationStep));
        updateElevatorDisplay();
        checkIfSimulationComplete();
    });

    // Connect Elevator State Updates to log console and handle boarding/disembarking
    for (Elevator* elevator : controlSystem->getElevators()) {
        connect(elevator, &Elevator::updateElevatorState,
                this, [this](int elevatorID, int floor, QString state) {
            ui->logText->append(QString("Elevator %1 is now at floor %2, state: %3")
                                .arg(elevatorID).arg(floor).arg(state));

            if (state == "Door Open") {
                // Disembark passengers whose destination matches the current floor
                // and who are on this elevator.
                for (Passenger* p : passengers) {
                    if (p->isOnElevator() &&
                        p->getDestinationFloor() == floor &&
                        !p->isFinished() &&
                        p->getBoardedElevatorID() == elevatorID)
                    {
                        ui->logText->append(
                            QString("Passenger %1 disembarks Elevator %2 at floor %3.")
                            .arg(p->getID()).arg(elevatorID).arg(floor)
                        );
                        p->markFinished();
                    }
                }
                //Board waiting passengers ONLY if there's no Fire alarm active
                // Then board waiting passengers at this floor
                if (!controlSystem->isFireActive()) {
                                    for (Passenger* p : passengers) {
                                        if (!p->isOnElevator() && (p->getStartFloor() == floor)) {
                                            ui->logText->append(
                                                QString("Passenger %1 boards Elevator %2 at floor %3. Destination = %4.")
                                                .arg(p->getID()).arg(elevatorID).arg(floor).arg(p->getDestinationFloor())
                                            );
                                            p->boardElevator(elevatorID);
                                        }
                                    }
                                } else {
                                    // If a fire alarm is active, log that no new passengers may board
                                    ui->logText->append("Fire alarm active: No new passengers may board.");
                                }
                            }
                        });
                    }





    // Qt's auto-connect,not need these lines;
    // but if you do, uncomment them:
    // connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::on_startButton_clicked);
    // connect(ui->pauseButton, &QPushButton::clicked, this, &MainWindow::on_pauseButton_clicked);
    // connect(ui->continueButton, &QPushButton::clicked, this, &MainWindow::on_continueButton_clicked);
    // connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::on_stopButton_clicked);

    // Safety Event Buttons
    connect(ui->fireButton,       &QPushButton::clicked, this, &MainWindow::on_fireButton_clicked);
    connect(ui->powerOutButton,   &QPushButton::clicked, this, &MainWindow::on_powerOutButton_clicked);

    // Elevator 1 Control
    connect(ui->elevator1Help,           &QPushButton::clicked, this, &MainWindow::on_elevator1Help_clicked);
    connect(ui->elevator1DoorObstacle,   &QPushButton::clicked, this, &MainWindow::on_elevator1DoorObstacle_clicked);
    connect(ui->elevator1Overload,       &QPushButton::clicked, this, &MainWindow::on_elevator1Overload_clicked);
    connect(ui->elevator1OpenDoor,       &QPushButton::clicked, this, &MainWindow::on_elevator1OpenDoor_clicked);
    connect(ui->elevator1CloseDoor,      &QPushButton::clicked, this, &MainWindow::on_elevator1CloseDoor_clicked);

    // Elevator 2 Control
    connect(ui->elevator2Help,           &QPushButton::clicked, this, &MainWindow::on_elevator2Help_clicked);
    connect(ui->elevator2DoorObstacle,   &QPushButton::clicked, this, &MainWindow::on_elevator2DoorObstacle_clicked);
    connect(ui->elevator2Overload,       &QPushButton::clicked, this, &MainWindow::on_elevator2Overload_clicked);
    connect(ui->elevator2OpenDoor,       &QPushButton::clicked, this, &MainWindow::on_elevator2OpenDoor_clicked);
    connect(ui->elevator2CloseDoor,      &QPushButton::clicked, this, &MainWindow::on_elevator2CloseDoor_clicked);

    // Connect ControlSystem's log update to our log console
    connect(controlSystem, &ControlSystem::updateSimulationLog, this, &MainWindow::updateLogConsole);

    // Placeholder text for passenger input
    ui->passengerSetupText->setPlaceholderText(
        "Enter passengers as: ID,StartFloor,DestFloor\n"
        "One passenger per line\n"
        "Example:\n1,1,5\n2,3,1\n3,5,2"
    );
}

MainWindow::~MainWindow() {
    delete ui;
}

// Simulation Control Slots
void MainWindow::on_startButton_clicked() {
    if (simulationStep != 0) {
        ui->logText->append("Simulation already running! Reset before starting again.");
        return;
    }
    simulationStep = 0;
    ui->simulationStepLabel->setText(QString("Simulation Step: %1").arg(simulationStep));
    simulationRunning = true;  // Start simulation.

    if (passengers.isEmpty()) {
        setupPassengers();
    }
    simulationTimer->start(1000);  // 1 second per step.

    // Schedule passenger requests after a short delay
    QTimer::singleShot(2000, this, [this]() {
        for (Passenger* p : passengers) {
            if (!p->hasRequestedElevator()) {
                int direction = (p->getDestinationFloor() > p->getStartFloor()) ? 1 : -1;
                ui->logText->append(
                    QString("Passenger %1 (start=%2, dest=%3) requesting elevator.")
                    .arg(p->getID()).arg(p->getStartFloor()).arg(p->getDestinationFloor())
                );
                p->requestElevator(direction);
                p->markElevatorRequested();
            }
        }
    });
    ui->logText->append("Simulation Started.");
}

void MainWindow::on_pauseButton_clicked() {
    simulationTimer->stop();
    simulationRunning = false;
    // Inform all elevators to suspend queued events
    for (Elevator* e : controlSystem->getElevators()) {
        e->setSimulationActive(false);
    }
    ui->logText->append("Simulation Paused.");
}

void MainWindow::on_continueButton_clicked() {
    simulationRunning = true;
    for (Elevator* e : controlSystem->getElevators()) {
        e->setSimulationActive(true);
    }
    simulationTimer->start(1000);
    ui->logText->append("Simulation Continued.");
}

void MainWindow::on_stopButton_clicked() {
    simulationTimer->stop();
    simulationStep = 0;
    simulationRunning = false;
    for (Elevator* e : controlSystem->getElevators()) {
        e->setSimulationActive(false);
    }
    ui->simulationStepLabel->setText(QString("Simulation Step: %1").arg(simulationStep));
    ui->logText->append("Simulation Stopped.");
}

// Passenger Setup
void MainWindow::setupPassengers() {
    QString passengerData = ui->passengerSetupText->toPlainText();
    QStringList lines = passengerData.split("\n", Qt::SkipEmptyParts);

    // Clear existing passengers
    qDeleteAll(passengers);
    passengers.clear();

    for (const QString& line : lines) {
        QStringList parts = line.split(",", Qt::SkipEmptyParts);
        if (parts.size() >= 3) {
            int id = parts[0].toInt();
            int startFloor = parts[1].toInt();
            int destFloor = parts[2].toInt();

            Passenger* passenger = new Passenger(id, startFloor, destFloor, this);
            passengers.append(passenger);

            connect(passenger, &Passenger::elevatorRequested, controlSystem, &ControlSystem::handleFloorRequest);
            connect(passenger, &Passenger::carRequest,        controlSystem, &ControlSystem::handleCarRequest);
        }
    }
    ui->logText->append(QString("Added %1 passengers to simulation.").arg(passengers.size()));
}

// Safety Event Functions
void MainWindow::on_fireButton_clicked() {
    ui->logText->append("Fire Alarm Triggered!");
    SafetyEvent fireEvent("Fire", 0, -1, this);
    controlSystem->handleSafetyEvent(&fireEvent);
}

void MainWindow::on_powerOutButton_clicked() {
    ui->logText->append("Power Outage Occurred!");
    SafetyEvent powerOutEvent("Power Out", 0, -1, this);
    controlSystem->handleSafetyEvent(&powerOutEvent);
}

// Elevator 1 Functions
void MainWindow::on_elevator1Help_clicked() {
    ui->logText->append("Elevator 0 Help Button Pressed.");
    controlSystem->handleSafetyEvent(new SafetyEvent("Help", 0, 0, this));
}

void MainWindow::on_elevator1DoorObstacle_clicked() {
    ui->logText->append("Elevator 0 Door Obstacle Detected.");
    controlSystem->handleSafetyEvent(new SafetyEvent("Door Obstacle", 0,0, this));
}

void MainWindow::on_elevator1Overload_clicked() {
    ui->logText->append("Elevator 0 Overloaded.");
    controlSystem->handleSafetyEvent(new SafetyEvent("Overload", 0, 0, this));
}

void MainWindow::on_elevator1OpenDoor_clicked() {
    ui->logText->append("Elevator 0 Door Opened.");
}

void MainWindow::on_elevator1CloseDoor_clicked() {
    ui->logText->append("Elevator 0 Door Closed.");
}

// Elevator 2 Functions
void MainWindow::on_elevator2Help_clicked() {
    ui->logText->append("Elevator 1 Help Button Pressed.");
    controlSystem->handleSafetyEvent(new SafetyEvent("Help", 0, 1, this));
}

void MainWindow::on_elevator2DoorObstacle_clicked() {
    ui->logText->append("Elevator 1 Door Obstacle Detected.");
    controlSystem->handleSafetyEvent(new SafetyEvent("Door Obstacle", 0, 1, this));
}

void MainWindow::on_elevator2Overload_clicked() {
    ui->logText->append("Elevator 1 Overloaded.");
    controlSystem->handleSafetyEvent(new SafetyEvent("Overload", 0, 1, this));
}

void MainWindow::on_elevator2OpenDoor_clicked() {
    ui->logText->append("Elevator 1 Door Opened.");
}

void MainWindow::on_elevator2CloseDoor_clicked() {
    ui->logText->append("Elevator 1 Door Closed.");
}

// Log Console Update
void MainWindow::updateLogConsole(QString message) {
    ui->logText->append(message);
}

// Elevator Display Update (if needed)
void MainWindow::updateElevatorDisplay() {
    // Optionally update any dedicated elevator display or widget
}

// Completion Check
void MainWindow::checkIfSimulationComplete() {
    bool allFinished = true;
    for (Passenger* p : passengers) {
        if (!p->isFinished()) {
            allFinished = false;
            break;
        }
    }

    bool allIdle = true;
    for (Elevator* e : controlSystem->getElevators()) {
        if (e->getState() != "idle") {
            allIdle = false;
            break;
        }
    }

    qDebug() << "checkIfSimulationComplete called."
             << "allFinished=" << allFinished
             << "allIdle=" << allIdle;

    if (allFinished && allIdle) {
        ui->logText->append("Simulation complete. All events handled and all elevators idle.");

        simulationTimer->stop();
        simulationRunning = false;

        // Forcefully disconnect & kill the timer so it can't fire again
        disconnect(simulationTimer, &QTimer::timeout, this, nullptr);
        simulationTimer->deleteLater();
        simulationTimer = nullptr;

        qDebug() << "Simulation truly complete. Timer destroyed.";
    }
}

