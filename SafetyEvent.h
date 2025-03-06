#ifndef SAFETYEVENT_H
#define SAFETYEVENT_H

#include <QObject>
#include <QString>

class SafetyEvent : public QObject {
    Q_OBJECT

public:
    explicit SafetyEvent(const QString& eventType, int timeStep, int elevatorID, QObject* parent = nullptr);

    void triggerEvent();
    void resolveEvent();

    QString getEventType() const;

      int getElevatorID() const;

signals:
    void safetyEventTriggered(QString eventType);

private:
    QString eventType;
    int timeStep;
    int elevatorID;
};

#endif // SAFETYEVENT_H

