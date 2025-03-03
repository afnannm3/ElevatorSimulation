#include "MainWindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      building(new Building(5, 2, this)),
      controlSystem(new ControlSystem(2, 5, this)) {

    ui->setupUi(this);

    // Initialize simulation step counter and timer
    simulationStep = 0;
    simulationTimer = new QTimer(this);
    connect(simulationTimer, &QTimer::timeout, this, [this]() {
        simulationStep++;
        ui->simulationStepLabel->setText(QString("Simulation Step: %1").arg(simulationStep));
        updateElevatorDisplay();
    });
    // Connect Elevator State Updates to Log Console
    for (Elevator* elevator : controlSystem->getElevators()) {
        connect(elevator, &Elevator::updateElevatorState,
                this, [this](int elevatorID, int floor, QString state) {
            ui->logText->append(QString("Elevator %1 is now at floor %2, state: %3")
                                .arg(elevatorID).arg(floor).arg(state));

            // If door just opened, board any waiting passengers
            if (state == "Door Open") {
                for (Passenger* p : passengers) {
                    // If passenger hasn't boarded yet and is on this floor
                    if (!p->isOnElevator() && (p->getStartFloor() == floor)) {
                        ui->logText->append(QString(
                            "Passenger %1 boards Elevator %2 at floor %3. Destination = %4."
                        ).arg(p->getID()).arg(elevatorID).arg(floor).arg(p->getDestinationFloor()));

                        // Mark passenger as on board, which triggers a carRequest
                        p->boardElevator(elevatorID);
                    }
                }
            }
        });
    }
    // Connect Simulation Control Buttons
    //connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::on_startButton_clicked);
    connect(ui->pauseButton, &QPushButton::clicked, this, &MainWindow::on_pauseButton_clicked);
    connect(ui->continueButton, &QPushButton::clicked, this, &MainWindow::on_continueButton_clicked);
    //connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::on_stopButton_clicked);

    // Connect Safety Event Buttons
    connect(ui->fireButton, &QPushButton::clicked, this, &MainWindow::on_fireButton_clicked);
    connect(ui->powerOutButton, &QPushButton::clicked, this, &MainWindow::on_powerOutButton_clicked);

    // Connect Elevator 1 Control Buttons
    connect(ui->elevator1Help, &QPushButton::clicked, this, &MainWindow::on_elevator1Help_clicked);
    connect(ui->elevator1DoorObstacle, &QPushButton::clicked, this, &MainWindow::on_elevator1DoorObstacle_clicked);
    connect(ui->elevator1Overload, &QPushButton::clicked, this, &MainWindow::on_elevator1Overload_clicked);
    connect(ui->elevator1OpenDoor, &QPushButton::clicked, this, &MainWindow::on_elevator1OpenDoor_clicked);
    connect(ui->elevator1CloseDoor, &QPushButton::clicked, this, &MainWindow::on_elevator1CloseDoor_clicked);

    // Connect Elevator 2 Control Buttons
    connect(ui->elevator2Help, &QPushButton::clicked, this, &MainWindow::on_elevator2Help_clicked);
    connect(ui->elevator2DoorObstacle, &QPushButton::clicked, this, &MainWindow::on_elevator2DoorObstacle_clicked);
    connect(ui->elevator2Overload, &QPushButton::clicked, this, &MainWindow::on_elevator2Overload_clicked);
    connect(ui->elevator2OpenDoor, &QPushButton::clicked, this, &MainWindow::on_elevator2OpenDoor_clicked);
    connect(ui->elevator2CloseDoor, &QPushButton::clicked, this, &MainWindow::on_elevator2CloseDoor_clicked);

    // Connect Simulation Log Update
    connect(controlSystem, &ControlSystem::updateSimulationLog, this, &MainWindow::updateLogConsole);

    // Setup Passenger Input Placeholder
    ui->passengerSetupText->setPlaceholderText("Enter passengers as: ID,StartFloor,DestFloor\n"
                                               "One passenger per line\n"
                                               "Example:\n"
                                               "1,1,5\n"
                                               "2,3,1\n"
                                               "3,5,2");
}

// Destructor
MainWindow::~MainWindow() {
    delete ui;
}

// ================== Simulation Control Functions ==================
void MainWindow::on_startButton_clicked() {

    qDebug() << "on_startButton_clicked() triggered!"; // <<-- ADDED


    if (simulationStep != 0) {
        ui->logText->append("Simulation already running! Reset before starting again.");
        return;  // Prevent multiple starts
    }

    simulationStep = 0;
    ui->simulationStepLabel->setText(QString("Simulation Step: %1").arg(simulationStep));

    //
    if (passengers.isEmpty()) {
        setupPassengers();
    }

    simulationTimer->start(1000); // 1 second per step

    // Ensure passengers only request an elevator once
    // Inside on_startButton_clicked()
    QTimer::singleShot(2000, this, [this]() {
        for (Passenger* p : passengers) {
            if (!p->hasRequestedElevator()) {  // ✅ Ensure they request only once
                int direction = (p->getDestinationFloor() > p->getStartFloor()) ? 1 : -1;
                ui->logText->append(QString("Passenger %1 (startFloor=%2, destFloor=%3) requesting elevator.")
                                    .arg(p->getID())
                                    .arg(p->getStartFloor())
                                    .arg(p->getDestinationFloor()));

                p->requestElevator(direction);
                p->markElevatorRequested();  // ✅ Mark as requested
            }
        }
    });


    ui->logText->append("Simulation Started.");
}


void MainWindow::on_pauseButton_clicked() {
    simulationTimer->stop();
    ui->logText->append("Simulation Paused.");
}

void MainWindow::on_continueButton_clicked() {
    simulationTimer->start(1000);
    ui->logText->append("Simulation Continued.");
}

void MainWindow::on_stopButton_clicked() {
    simulationTimer->stop();
    simulationStep = 0;
    ui->simulationStepLabel->setText(QString("Simulation Step: %1").arg(simulationStep));
    ui->logText->append("Simulation Stopped.");
}

// ================== Passenger Setup ==================
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
        }
    }

    ui->logText->append(QString("Added %1 passengers to simulation.").arg(passengers.size()));
}




// ================== Safety Event Functions ==================
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

// ================== Elevator 1 Functions ==================
void MainWindow::on_elevator1Help_clicked() {
    ui->logText->append("Elevator 1 Help Button Pressed.");
    controlSystem->handleSafetyEvent(new SafetyEvent("Help", 0, 1, this));
}

void MainWindow::on_elevator1DoorObstacle_clicked() {
    ui->logText->append("Elevator 1 Door Obstacle Detected.");
    controlSystem->handleSafetyEvent(new SafetyEvent("Door Obstacle", 0, 1, this));
}

void MainWindow::on_elevator1Overload_clicked() {
    ui->logText->append("Elevator 1 Overloaded.");
    controlSystem->handleSafetyEvent(new SafetyEvent("Overload", 0, 1, this));
}

void MainWindow::on_elevator1OpenDoor_clicked() {
    ui->logText->append("Elevator 1 Door Opened.");
}

void MainWindow::on_elevator1CloseDoor_clicked() {
    ui->logText->append("Elevator 1 Door Closed.");
}

// ================== Elevator 2 Functions ==================
void MainWindow::on_elevator2Help_clicked() {
    ui->logText->append("Elevator 2 Help Button Pressed.");
    controlSystem->handleSafetyEvent(new SafetyEvent("Help", 0, 2, this));
}

void MainWindow::on_elevator2DoorObstacle_clicked() {
    ui->logText->append("Elevator 2 Door Obstacle Detected.");
    controlSystem->handleSafetyEvent(new SafetyEvent("Door Obstacle", 0, 2, this));
}

void MainWindow::on_elevator2Overload_clicked() {
    ui->logText->append("Elevator 2 Overloaded.");
    controlSystem->handleSafetyEvent(new SafetyEvent("Overload", 0, 2, this));
}

void MainWindow::on_elevator2OpenDoor_clicked() {
    ui->logText->append("Elevator 2 Door Opened.");
}

void MainWindow::on_elevator2CloseDoor_clicked() {
    ui->logText->append("Elevator 2 Door Closed.");
}
// ================== Log Console Update ==================
void MainWindow::updateLogConsole(QString message) {
    ui->logText->append(message);
}


// ================== Elevator Display ==================
void MainWindow::updateElevatorDisplay() {
//    for (Elevator* elevator : controlSystem->getElevators()) {
//        ui->logText->append(QString("Elevator %1: Floor %2, State: %3")
//                            .arg(elevator->property("elevatorID").toInt())
//                            .arg(elevator->getCurrentFloor())
//                            .arg(elevator->getState()));
//    }
}

