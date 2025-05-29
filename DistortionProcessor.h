#pragma once
#include <JuceHeader.h>

class DistortionProcessor {
public:
    void process(juce::AudioBuffer<float>& buffer) {
        for (int channel = 0; channel < buffer.getNumChannels(); channel++) {
            auto* channelData = buffer.getWritePointer(channel);

            for (int i = 0; i < buffer.getNumSamples(); i++) {
                // Жесткое ограничение
                float x = channelData[i] * juce::Decibels::decibelsToGain(drive);
                channelData[i] = juce::jlimit(-0.8f, 0.8f, x);
            }
        }
    }

    void setDrive(float newDrive) { drive = newDrive; }

private:
    float drive = 6.0f; // в децибелах
};