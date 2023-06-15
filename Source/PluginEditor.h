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

    juce::TextEditor inputNotesMessageBox;
    juce::TextEditor inputChordMessageBox;
    CustomMidiKeyboardComponent inputKeyboardComponent;
    juce::Slider octTransposeSlider;
    juce::Slider stTransposeSlider;
    juce::TextEditor outputNotesMessageBox;
    juce::TextEditor outputChordMessageBox;
    CustomMidiKeyboardComponent outputKeyboardComponent;
    
    

    void writeLog(const juce::String&);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(JamsterScannerAudioProcessorEditor)
};
