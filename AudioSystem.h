#ifndef AUDIOSYSTEM_H
#define AUDIOSYSTEM_H

#include <QObject>
#include <QString>

class AudioSystem : public QObject {
    Q_OBJECT

public:
    explicit AudioSystem(QObject* parent = nullptr);

    void playWarning(const QString& message);
    void stopWarning();

signals:
    void warningPlayed(QString message);

private:
    QString currentMessage;
};

#endif // AUDIOSYSTEM_H



