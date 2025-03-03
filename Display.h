#ifndef DISPLAY_H
#define DISPLAY_H

#include <QObject>
#include <QString>

class Display : public QObject {
    Q_OBJECT

public:
    explicit Display(QObject* parent = nullptr);

    void updateDisplay(int currentFloor, const QString& warningMessage);
    QString getWarningMessage() const;

signals:
    void displayUpdated(int currentFloor, QString warningMessage);

private:
    int currentFloor;
    QString warningMessage;
};

#endif // DISPLAY_H
