/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomMidiKeyboardComponent.h"

//==============================================================================
/**
*/
class JamsterScannerAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    JamsterScannerAudioProcessorEditor(JamsterScannerAudioProcessor&);
    ~JamsterScannerAudioProcessorEditor();

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

    void logMidiMessage(const juce::MidiMessage&);
    void addListener(juce::Button::Listener*);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JamsterScannerAudioProcessor& processor;

    CustomMidiKeyboardComponent keyboardComponent;
    juce::Label metronomeLabel;
    juce::ToggleButton metronomeButton;
    juce::TextButton resetButton;
    juce::TextEditor midiMessagesBox;

    double curBPM = 0.0;
    int curBeat = 0;
    double timeElapsed = 0.0;
    long long samplesElapsed = 0;

    static juce::String getMidiMessageDescription(const juce::MidiMessage&);
    void writeLog(const juce::String&);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(JamsterScannerAudioProcessorEditor)
};
