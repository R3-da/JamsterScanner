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
    : AudioProcessorEditor(&p), processor(p), inputKeyboardComponent(p.inputKeyboardState, juce::MidiKeyboardComponent::horizontalKeyboard),
    outputKeyboardComponent(p.outputKeyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{
    inputNotesLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    inputNotesLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(inputNotesLabel);

    inputNotesMessageBox.setMultiLine(false);
    inputNotesMessageBox.setReadOnly(true);
    inputNotesMessageBox.setCaretVisible(false);
    inputNotesMessageBox.setPopupMenuEnabled(false);
    inputNotesMessageBox.setJustification(juce::Justification::centred);
    inputNotesMessageBox.setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x32ffffff));
    inputNotesMessageBox.setColour(juce::TextEditor::outlineColourId, juce::Colour(0x1c000000));
    inputNotesMessageBox.setColour(juce::TextEditor::shadowColourId, juce::Colour(0x16000000));
    addAndMakeVisible(inputNotesMessageBox);

    inputChordLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    inputChordLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(inputChordLabel);

    inputChordMessageBox.setMultiLine(false);
    inputChordMessageBox.setReadOnly(true);
    inputChordMessageBox.setCaretVisible(false);
    inputChordMessageBox.setPopupMenuEnabled(false);
    inputChordMessageBox.setJustification(juce::Justification::centred);
    inputChordMessageBox.setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x32ffffff));
    inputChordMessageBox.setColour(juce::TextEditor::outlineColourId, juce::Colour(0x1c000000));
    inputChordMessageBox.setColour(juce::TextEditor::shadowColourId, juce::Colour(0x16000000));
    addAndMakeVisible(inputChordMessageBox);

    inputKeyboardComponent.setKeyWidth(19.0f);
    inputKeyboardComponent.setAvailableRange(0, 120);
    inputKeyboardComponent.setOctaveForMiddleC(5);
    inputKeyboardComponent.setLowestVisibleKey(30);
    addAndMakeVisible(inputKeyboardComponent);

    octTransposeSlider.setRange(-10, 10, 1);
    octTransposeSlider.setTextValueSuffix(" Oct");
    addAndMakeVisible(octTransposeSlider);

    stTransposeSlider.setRange(-12, 12, 1);
    stTransposeSlider.setTextValueSuffix(" St");
    addAndMakeVisible(stTransposeSlider);

    outputNotesLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    outputNotesLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(outputNotesLabel);

    outputNotesMessageBox.setMultiLine(false);
    outputNotesMessageBox.setReadOnly(true);
    outputNotesMessageBox.setCaretVisible(false);
    outputNotesMessageBox.setPopupMenuEnabled(false);
    outputNotesMessageBox.setJustification(juce::Justification::centred);
    outputNotesMessageBox.setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x32ffffff));
    outputNotesMessageBox.setColour(juce::TextEditor::outlineColourId, juce::Colour(0x1c000000));
    outputNotesMessageBox.setColour(juce::TextEditor::shadowColourId, juce::Colour(0x16000000));
    addAndMakeVisible(outputNotesMessageBox);

    outputChordLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    outputChordLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(outputChordLabel);

    outputChordMessageBox.setMultiLine(false);
    outputChordMessageBox.setReadOnly(true);
    outputChordMessageBox.setCaretVisible(false);
    outputChordMessageBox.setPopupMenuEnabled(false);
    outputChordMessageBox.setJustification(juce::Justification::centred);
    outputChordMessageBox.setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x32ffffff));
    outputChordMessageBox.setColour(juce::TextEditor::outlineColourId, juce::Colour(0x1c000000));
    outputChordMessageBox.setColour(juce::TextEditor::shadowColourId, juce::Colour(0x16000000));
    addAndMakeVisible(outputChordMessageBox);

    outputKeyboardComponent.setKeyWidth(19.0f);
    outputKeyboardComponent.setAvailableRange(0, 120);
    outputKeyboardComponent.setOctaveForMiddleC(5);
    outputKeyboardComponent.setLowestVisibleKey(30);
    addAndMakeVisible(outputKeyboardComponent);

    addListeners(this);
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
    
    int labelHeight = 25;
    int keyboardHeight = 80;
    int textBoxHeight = 40;
    int sliderBoxWidth = 300;
    int sliderBoxHeight = 40;

    // Calculate the bounds for the left text box
    juce::Rectangle<int> inputNotesLabelBounds = getLocalBounds()
        .withHeight(labelHeight)
        .removeFromLeft(getWidth() / 2);

    // Calculate the bounds for the left text box
    juce::Rectangle<int> inputChordLabelBounds = getLocalBounds()
        .withHeight(labelHeight)
        .removeFromRight(getWidth() / 2);

    // Calculate the bounds for the left text box
    juce::Rectangle<int> inputNotesBoxBounds = getLocalBounds()
        .withHeight(textBoxHeight)
        .removeFromLeft(getWidth() / 2)
        .withY(inputNotesLabelBounds.getBottom() - 8)
        .reduced(8); // Divide the width in half for two equal boxes

    // Calculate the bounds for the right text box
    juce::Rectangle<int> inputChordBoxBounds = getLocalBounds()
        .withHeight(textBoxHeight)
        .removeFromRight(getWidth() / 2)
        .withY(inputNotesLabelBounds.getBottom() - 8)
        .reduced(8); // Divide the width in half for two equal boxes

    // Calculate the bounds for the keyboard component
    juce::Rectangle<int> inputKeyboardBounds = getLocalBounds()
        .removeFromTop(keyboardHeight)
        .withY(inputNotesBoxBounds.getBottom() + 8)
        .reduced(8);

    // Calculate the bounds for the keyboard component
    juce::Rectangle<int> outputKeyboardBounds = getLocalBounds()
        .removeFromBottom(keyboardHeight) // Remove from the bottom instead of the top
        .reduced(8);

    // Calculate the bounds for the left text box
    juce::Rectangle<int> outputNotesBoxBounds = getLocalBounds()
        .withHeight(textBoxHeight)
        .removeFromLeft(getWidth() / 2)
        .withY(outputKeyboardBounds.getY() - (textBoxHeight + 8))
        .reduced(8); // Divide the width in half for two equal boxes

    // Calculate the bounds for the right text box
    juce::Rectangle<int> outputChordBoxBounds = getLocalBounds()
        .withHeight(textBoxHeight)
        .removeFromRight(getWidth() / 2)
        .withY(outputKeyboardBounds.getY() - (textBoxHeight + 8))
        .reduced(8); // Divide the width in half for two equal boxes

    // Calculate the bounds for the left text box
    juce::Rectangle<int> outputNotesLabelBounds = getLocalBounds()
        .withHeight(labelHeight)
        .removeFromLeft(getWidth() / 2)
        .withY(outputNotesBoxBounds.getY() - (labelHeight));

    // Calculate the bounds for the left text box
    juce::Rectangle<int> outputChordLabelBounds = getLocalBounds()
        .withHeight(labelHeight)
        .removeFromRight(getWidth() / 2)
        .withY(outputNotesBoxBounds.getY() - (labelHeight));

    // Calculate the bounds for the keyboard component
    juce::Rectangle<int> octSliderBounds = getLocalBounds()
        .removeFromTop(sliderBoxHeight)
        .withWidth(sliderBoxWidth)
        .withY((outputNotesLabelBounds.getY() - (outputNotesLabelBounds.getY() - inputKeyboardBounds.getY()) / 2) - sliderBoxHeight / 2)
        .withX(getLocalBounds().getCentreX() - sliderBoxWidth / 2)
        .reduced(8);

    // Calculate the bounds for the keyboard component
    juce::Rectangle<int> stSliderBounds = getLocalBounds()
        .removeFromTop(sliderBoxHeight)
        .withWidth(sliderBoxWidth)
        .withY((outputNotesBoxBounds.getY() - (outputNotesBoxBounds.getY() - inputKeyboardBounds.getY()) / 2) + sliderBoxHeight / 2)
        .withX(getLocalBounds().getCentreX() - sliderBoxWidth / 2)
        .reduced(8);

    // Set the bounds for the left text box, right text box, and keyboard component
    inputNotesLabel.setBounds(inputNotesLabelBounds);
    inputNotesMessageBox.setBounds(inputNotesBoxBounds);
    inputChordLabel.setBounds(inputChordLabelBounds);
    inputChordMessageBox.setBounds(inputChordBoxBounds);
    inputKeyboardComponent.setBounds(inputKeyboardBounds);
    octTransposeSlider.setBounds(octSliderBounds);
    stTransposeSlider.setBounds(stSliderBounds);
    outputNotesLabel.setBounds(outputNotesLabelBounds);
    outputNotesMessageBox.setBounds(outputNotesBoxBounds);
    outputChordLabel.setBounds(outputChordLabelBounds);
    outputChordMessageBox.setBounds(outputChordBoxBounds);
    outputKeyboardComponent.setBounds(outputKeyboardBounds);
}

void JamsterScannerAudioProcessorEditor::logInputNotes(const int& message)
{
    inputWriteNotes(juce::MidiMessage::getMidiNoteName(message, true, true, 5));
}

void JamsterScannerAudioProcessorEditor::clearInputNotes() {
    inputNotesMessageBox.clear();
}

void JamsterScannerAudioProcessorEditor::logInputChord(const juce::Array<int> myNumbers)
{
    //inputWriteChord(juce::MidiMessage::getMidiNoteName(message, true, true, 5));
    //juce::Array<int> myNumbers = { 60, 64, 67 };

    auto outputTest2 = chordDetector.getChordsIndexStartPoint(myNumbers);
    inputWriteChord(outputTest2);
}

void JamsterScannerAudioProcessorEditor::clearInputChord() {
    inputChordMessageBox.clear();
}

void JamsterScannerAudioProcessorEditor::logOutputNotes(const int& message)
{
    outputWriteNotes(juce::MidiMessage::getMidiNoteName(message, true, true, 5));
}

void JamsterScannerAudioProcessorEditor::clearOutputNotes() {
    outputNotesMessageBox.clear();
}

void JamsterScannerAudioProcessorEditor::logOutputChord(const juce::Array<int> myNumbers)
{
    auto outputTest2 = chordDetector.getChordsIndexStartPoint(myNumbers);
    outputWriteChord(outputTest2);
}

void JamsterScannerAudioProcessorEditor::clearOutputChord() {
    outputChordMessageBox.clear();
}

void JamsterScannerAudioProcessorEditor::addListeners(juce::Slider::Listener* listener) {
    octTransposeSlider.addListener(listener);
    stTransposeSlider.addListener(listener);
}

void JamsterScannerAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    processor.sliderChanged();
    if (slider == &octTransposeSlider) {
        processor.setOctTransposeValue((int)octTransposeSlider.getValue());
    }
    if (slider == &stTransposeSlider) {
        processor.setStTransposeValue((int)stTransposeSlider.getValue()) ;
    }
}

//==============================================================================

void JamsterScannerAudioProcessorEditor::inputWriteNotes(const juce::String& m)
{
    inputNotesMessageBox.insertTextAtCaret(" " + m + " ");
}

void JamsterScannerAudioProcessorEditor::inputWriteChord(const juce::Array<ChordIndexStartpoint>& m)
{
    juce::String noteName;
    for (int i = 0; i < m.size(); ++i)
    {
        noteName = juce::MidiMessage::getMidiNoteName(chordDetector.getNoteIndex(m[i].startpoint), true, true, 5);
        noteName = noteName.dropLastCharacters(1);
        inputChordMessageBox.insertTextAtCaret(noteName);
        inputChordMessageBox.insertTextAtCaret(chordDetector.chordsList[m[i].index].postfix + " ");
    }
}

void JamsterScannerAudioProcessorEditor::outputWriteNotes(const juce::String& m)
{
    outputNotesMessageBox.insertTextAtCaret(" " + m + " ");
}

void JamsterScannerAudioProcessorEditor::outputWriteChord(const juce::Array<ChordIndexStartpoint>& m)
{
    juce::String noteName;
    for (int i = 0; i < m.size(); ++i)
    {
        noteName = juce::MidiMessage::getMidiNoteName(chordDetector.getNoteIndex(m[i].startpoint), true, true, 5);
        noteName = noteName.dropLastCharacters(1);
        outputChordMessageBox.insertTextAtCaret(noteName);
        outputChordMessageBox.insertTextAtCaret(chordDetector.chordsList[m[i].index].postfix + " ");
    }
}
