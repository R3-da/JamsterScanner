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
    inputNotesMessageBox.setMultiLine(false);
    inputNotesMessageBox.setReadOnly(true);
    inputNotesMessageBox.setCaretVisible(false);
    inputNotesMessageBox.setPopupMenuEnabled(false);
    inputNotesMessageBox.setJustification(juce::Justification::centred);
    inputNotesMessageBox.setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x32ffffff));
    inputNotesMessageBox.setColour(juce::TextEditor::outlineColourId, juce::Colour(0x1c000000));
    inputNotesMessageBox.setColour(juce::TextEditor::shadowColourId, juce::Colour(0x16000000));
    addAndMakeVisible(inputNotesMessageBox);

    inputChordMessageBox.setMultiLine(false);
    inputChordMessageBox.setReadOnly(true);
    inputChordMessageBox.setCaretVisible(false);
    inputChordMessageBox.setPopupMenuEnabled(false);
    inputChordMessageBox.setJustification(juce::Justification::centred);
    inputChordMessageBox.setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x32ffffff));
    inputChordMessageBox.setColour(juce::TextEditor::outlineColourId, juce::Colour(0x1c000000));
    inputChordMessageBox.setColour(juce::TextEditor::shadowColourId, juce::Colour(0x16000000));
    addAndMakeVisible(inputChordMessageBox);

    outputNotesMessageBox.setMultiLine(false);
    outputNotesMessageBox.setReadOnly(true);
    outputNotesMessageBox.setCaretVisible(false);
    outputNotesMessageBox.setPopupMenuEnabled(false);
    outputNotesMessageBox.setJustification(juce::Justification::centred);
    outputNotesMessageBox.setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x32ffffff));
    outputNotesMessageBox.setColour(juce::TextEditor::outlineColourId, juce::Colour(0x1c000000));
    outputNotesMessageBox.setColour(juce::TextEditor::shadowColourId, juce::Colour(0x16000000));
    addAndMakeVisible(outputNotesMessageBox);

    keyboardComponent.setKeyWidth(19.0f);
    keyboardComponent.setAvailableRange(0, 120);
    keyboardComponent.setOctaveForMiddleC(5);
    keyboardComponent.setLowestVisibleKey(30);
    addAndMakeVisible(keyboardComponent);

    octTransposeSlider.setRange(-10, 10, 1);
    addAndMakeVisible(octTransposeSlider);

    stTransposeSlider.setRange(-12, 12, 1);
    addAndMakeVisible(stTransposeSlider);

    outputChordMessageBox.setMultiLine(false);
    outputChordMessageBox.setReadOnly(true);
    outputChordMessageBox.setCaretVisible(false);
    outputChordMessageBox.setPopupMenuEnabled(false);
    outputChordMessageBox.setJustification(juce::Justification::centred);
    outputChordMessageBox.setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x32ffffff));
    outputChordMessageBox.setColour(juce::TextEditor::outlineColourId, juce::Colour(0x1c000000));
    outputChordMessageBox.setColour(juce::TextEditor::shadowColourId, juce::Colour(0x16000000));
    addAndMakeVisible(outputChordMessageBox);

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
    int sliderBoxWidth = 300;
    int sliderBoxHeight = 40;

    // Calculate the bounds for the left text box
    juce::Rectangle<int> inputNotesBoxBounds = getLocalBounds()
        .withHeight(textBoxHeight)
        .removeFromLeft(getWidth() / 2)
        .reduced(8); // Divide the width in half for two equal boxes

    // Calculate the bounds for the right text box
    juce::Rectangle<int> inputChordBoxBounds = getLocalBounds()
        .withHeight(textBoxHeight)
        .removeFromRight(getWidth() / 2)
        .reduced(8); // Divide the width in half for two equal boxes

    // Calculate the bounds for the keyboard component
    juce::Rectangle<int> keyboardBounds = getLocalBounds()
        .removeFromTop(keyboardHeight)
        .withY(inputNotesBoxBounds.getBottom())
        .reduced(8);

    // Calculate the bounds for the keyboard component
    juce::Rectangle<int> octSliderBounds = getLocalBounds()
        .removeFromTop(sliderBoxHeight)
        .withWidth(sliderBoxWidth)
        .withY(keyboardBounds.getBottom())
        .withX(getLocalBounds().getCentreX() - sliderBoxWidth / 2)
        .reduced(8);

    // Calculate the bounds for the keyboard component
    juce::Rectangle<int> stSliderBounds = getLocalBounds()
        .removeFromTop(sliderBoxHeight)
        .withWidth(sliderBoxWidth)
        .withY(octSliderBounds.getBottom())
        .withX(getLocalBounds().getCentreX() - sliderBoxWidth / 2)
        .reduced(8);   

    // Calculate the bounds for the left text box
    juce::Rectangle<int> outputNotesBoxBounds = getLocalBounds()
        .withHeight(textBoxHeight)
        .removeFromLeft(getWidth() / 2)
        .withY(stSliderBounds.getBottom())
        .reduced(8); // Divide the width in half for two equal boxes

    // Calculate the bounds for the right text box
    juce::Rectangle<int> outputChordBoxBounds = getLocalBounds()
        .withHeight(textBoxHeight)
        .removeFromRight(getWidth() / 2)
        .withY(stSliderBounds.getBottom())
        .reduced(8); // Divide the width in half for two equal boxes

    // Set the bounds for the left text box, right text box, and keyboard component
    inputNotesMessageBox.setBounds(inputNotesBoxBounds);
    inputChordMessageBox.setBounds(inputChordBoxBounds);
    keyboardComponent.setBounds(keyboardBounds);
    octTransposeSlider.setBounds(octSliderBounds);
    stTransposeSlider.setBounds(stSliderBounds);
    outputNotesMessageBox.setBounds(outputNotesBoxBounds);
    outputChordMessageBox.setBounds(outputChordBoxBounds);
}

void JamsterScannerAudioProcessorEditor::logMidiMessage(const int& message)
{
    writeLog(juce::MidiMessage::getMidiNoteName(message, true, true, 5));
}

void JamsterScannerAudioProcessorEditor::clearMessageBox() {
    inputNotesMessageBox.clear();
}

//==============================================================================

void JamsterScannerAudioProcessorEditor::writeLog(const juce::String& m)
{
    inputNotesMessageBox.insertTextAtCaret(" " + m + " ");
}
