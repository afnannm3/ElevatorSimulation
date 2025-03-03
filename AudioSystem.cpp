#include "AudioSystem.h"

AudioSystem::AudioSystem(QObject* parent) : QObject(parent) {}

void AudioSystem::playWarning(const QString& message) {
    emit warningPlayed(message);
}

void AudioSystem::stopWarning() {
    emit warningPlayed("");
}

