/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Настройка слайдеров
    setupSlider(driveSlider, "Drive");
    setupSlider(toneSlider, "Tone");
    setupSlider(volumeSlider, "Volume");

    // Кнопка ручного щипка
    pluckButton.setButtonText("PLUCK");
    pluckButton.onClick = [this] {
        audioProcessor.pluckString(220.0f); // A3
        };
    addAndMakeVisible(pluckButton);

    setSize(400, 300);

}
void NewProjectAudioProcessorEditor::setupSlider(juce::Slider& slider, const juce::String& name) {
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    slider.setName(name);
    addAndMakeVisible(slider);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::darkgrey);
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText("GUITAR SYNTH", getLocalBounds().removeFromTop(50), juce::Justification::centred);
}

void NewProjectAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced(20).removeFromBottom(150);

    driveSlider.setBounds(area.removeFromLeft(100));
    toneSlider.setBounds(area.removeFromLeft(100));
    volumeSlider.setBounds(area.removeFromLeft(100));
    pluckButton.setBounds(area.withSize(100, 50));
}
