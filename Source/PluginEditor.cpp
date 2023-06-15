/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JamsterScannerAudioProcessorEditor::JamsterScannerAudioProcessorEditor(JamsterScannerAudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p), keyboardComponent(p.keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{
    addAndMakeVisible(midiMessagesBox);
    midiMessagesBox.setMultiLine(false);
    midiMessagesBox.setReadOnly(true);
    midiMessagesBox.setCaretVisible(false);
    midiMessagesBox.setPopupMenuEnabled(false);
    midiMessagesBox.setJustification(juce::Justification::centred);
    midiMessagesBox.setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x32ffffff));
    midiMessagesBox.setColour(juce::TextEditor::outlineColourId, juce::Colour(0x1c000000));
    midiMessagesBox.setColour(juce::TextEditor::shadowColourId, juce::Colour(0x16000000));

    keyboardComponent.setKeyWidth(19.0f);
    keyboardComponent.setAvailableRange(0, 120);
    keyboardComponent.setOctaveForMiddleC(5);
    keyboardComponent.setLowestVisibleKey(30);
    addAndMakeVisible(keyboardComponent);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(700, 500);
}

JamsterScannerAudioProcessorEditor::~JamsterScannerAudioProcessorEditor()
{
}

//==============================================================================
void JamsterScannerAudioProcessorEditor::paint(juce::Graphics& g) {

}

void JamsterScannerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..


    int keyboardHeight = 80;
    int textBoxHeight = 40;

    // Calculate the bounds for the text box
    juce::Rectangle<int> textBoxBounds = getLocalBounds()
        .withHeight(textBoxHeight)
        .reduced(8);

    // Calculate the bounds for the keyboard component
    juce::Rectangle<int> keyboardBounds = getLocalBounds()
        .removeFromTop(keyboardHeight)
        .withY(textBoxBounds.getBottom())
        .reduced(8);

    // Set the bounds for the text box and keyboard component
    midiMessagesBox.setBounds(textBoxBounds);
    keyboardComponent.setBounds(keyboardBounds);
}

void JamsterScannerAudioProcessorEditor::logMidiMessage(const int& message)
{
    writeLog(juce::MidiMessage::getMidiNoteName(message, true, true, 5));
}

void JamsterScannerAudioProcessorEditor::clearMessageBox() {
    midiMessagesBox.clear();
}

//==============================================================================

void JamsterScannerAudioProcessorEditor::writeLog(const juce::String& m)
{
    midiMessagesBox.insertTextAtCaret(" " + m + " ");
}
