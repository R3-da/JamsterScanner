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
#include "ChordDetector.h"

//==============================================================================
/**
*/
class JamsterScannerAudioProcessorEditor : public juce::AudioProcessorEditor,
    public juce::Slider::Listener
{
public:
    JamsterScannerAudioProcessorEditor(JamsterScannerAudioProcessor&);
    ~JamsterScannerAudioProcessorEditor();

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

    void logInputNotes(const int&);
    void clearInputNotes();

    void logInputChord(const juce::Array<int>);
    void clearInputChord();

    void logOutputNotes(const int&);
    void clearOutputNotes();

    void logOutputChord(const juce::Array<int>);
    void clearOutputChord();

    void addListeners(juce::Slider::Listener*);

    void sliderValueChanged(juce::Slider* slider) override;

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

    ChordDetector chordDetector;

    void inputWriteNotes(const juce::String&);
    void outputWriteNotes(const juce::String&);
    void inputWriteChord(const juce::Array<ChordIndexStartpoint>& m);
    void outputWriteChord(const juce::Array<ChordIndexStartpoint>& m);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(JamsterScannerAudioProcessorEditor)
};
