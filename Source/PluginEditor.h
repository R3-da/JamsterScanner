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

    void logMidiMessage(const int&);
    void clearMessageBox();

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JamsterScannerAudioProcessor& processor;

    CustomMidiKeyboardComponent keyboardComponent;
    juce::Label metronomeLabel;
    juce::ToggleButton metronomeButton;
    juce::TextButton resetButton;
    juce::TextEditor midiMessagesBox;

    void writeLog(const juce::String&);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(JamsterScannerAudioProcessorEditor)
};
