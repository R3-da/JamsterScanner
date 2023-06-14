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
    keyboardComponent.setKeyWidth(19.0f);
    keyboardComponent.setAvailableRange(0, 120);
    keyboardComponent.setOctaveForMiddleC(5);
    keyboardComponent.setLowestVisibleKey(30);
    addAndMakeVisible(keyboardComponent);

    addAndMakeVisible(midiMessagesBox);
    midiMessagesBox.setMultiLine(true);
    midiMessagesBox.setReturnKeyStartsNewLine(true);
    midiMessagesBox.setReadOnly(true);
    midiMessagesBox.setScrollbarsShown(true);
    midiMessagesBox.setCaretVisible(false);
    midiMessagesBox.setPopupMenuEnabled(true);
    midiMessagesBox.setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x32ffffff));
    midiMessagesBox.setColour(juce::TextEditor::outlineColourId, juce::Colour(0x1c000000));
    midiMessagesBox.setColour(juce::TextEditor::shadowColourId, juce::Colour(0x16000000));

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

    auto quarterHeight = getHeight() / 4;
    auto halfWidth = getWidth() / 2;

    midiMessagesBox.setBounds(
        getLocalBounds().withHeight(getHeight() - quarterHeight)
        .withY(quarterHeight)
        .reduced(10));

    keyboardComponent.setBounds(
        getLocalBounds().removeFromTop(80)
        .reduced(8));
}

void JamsterScannerAudioProcessorEditor::logMidiMessage(const juce::MidiMessage& message)
{
    writeLog(juce::MidiMessage::getMidiNoteName(message.getNoteNumber(), true, true, 5));
}


//==============================================================================

void JamsterScannerAudioProcessorEditor::writeLog(const juce::String& m)
{
    midiMessagesBox.moveCaretToEnd();
    midiMessagesBox.insertTextAtCaret(m + juce::newLine);
}
