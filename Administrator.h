#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <QObject>
#include <QString>

class Administrator : public QObject {
    Q_OBJECT

public:
    explicit Administrator(const QString& name, QObject* parent = nullptr);
    
    void setupSimulation(int numFloors, int numElevators, int numPassengers);
    void startSimulation();
    void pauseSimulation();
    void stopSimulation();

private:
    QString name;
    bool simulationRunning;
};

#endif // ADMINISTRATOR_H

