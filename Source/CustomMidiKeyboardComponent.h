#pragma once

#include <JuceHeader.h>

class CustomMidiKeyboardComponent : public juce::MidiKeyboardComponent
{
public:
    CustomMidiKeyboardComponent(juce::MidiKeyboardState& state, juce::MidiKeyboardComponent::Orientation orientation);
    ~CustomMidiKeyboardComponent();

private:

    juce::String getWhiteNoteText(int midiNoteNumber) override;
    void drawWhiteNote(int midiNoteNumber, juce::Graphics& g, juce::Rectangle<float> area,
        bool isDown, bool isOver, juce::Colour lineColour, juce::Colour textColour) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomMidiKeyboardComponent)
};
