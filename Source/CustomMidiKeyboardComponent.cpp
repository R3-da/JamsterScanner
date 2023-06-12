#include "CustomMidiKeyboardComponent.h"
#include <JuceHeader.h>


CustomMidiKeyboardComponent::CustomMidiKeyboardComponent(juce::MidiKeyboardState& keyboardState, juce::MidiKeyboardComponent::Orientation orientation)
    : MidiKeyboardComponent(keyboardState, orientation)
{
}

CustomMidiKeyboardComponent::~CustomMidiKeyboardComponent()
{
}
juce::String CustomMidiKeyboardComponent::getWhiteNoteText(int midiNoteNumber)
{
    return juce::MidiMessage::getMidiNoteName(midiNoteNumber, true, true, getOctaveForMiddleC());
}




