/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JamsterScannerAudioProcessorEditor::JamsterScannerAudioProcessorEditor (JamsterScannerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), midiKeyboard(p.keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    midiKeyboard.setKeyWidth(20.0f);
    midiKeyboard.setAvailableRange(0, 120);
    addAndMakeVisible(midiKeyboard);

    setSize (700, 500);
}

JamsterScannerAudioProcessorEditor::~JamsterScannerAudioProcessorEditor()
{
}

//==============================================================================
void JamsterScannerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void JamsterScannerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto r = getLocalBounds().reduced(8);

    midiKeyboard.setBounds(r.removeFromBottom(70));
}