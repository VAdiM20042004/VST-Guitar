#pragma once
#include <JuceHeader.h>

class GuitarString {
public:
    void pluck(float frequency, float sampleRate) {
        int delaySamples = static_cast<int>(sampleRate / frequency);
        delayBuffer.setSize(1, delaySamples);
        delayBuffer.clear();

        // Заполняем шумом (имитация щипка)
        for (int i = 0; i < delaySamples; i++) {
            delayBuffer.setSample(0, i, random.nextFloat() * 2.0f - 1.0f);
        }

        writePointer = 0;
        filterState = 0.0f;
        this->frequency = frequency;
    }

    float process() {
        if (delayBuffer.getNumSamples() == 0) return 0.0f;

        int readPointer = (writePointer + 1) % delayBuffer.getNumSamples();
        float x = delayBuffer.getSample(0, readPointer);

        // Фильтр низких частот (затухание высоких гармоник)
        float y = 0.5f * (x + filterState);
        filterState = x;

        // Обновление буфера
        delayBuffer.setSample(0, writePointer, y);
        writePointer = readPointer;

        return y;
    }

private:
    juce::AudioBuffer<float> delayBuffer;
    int writePointer = 0;
    float filterState = 0.0f;
    float frequency = 0.0f;
    juce::Random random;
};