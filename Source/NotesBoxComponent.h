/*
  ==============================================================================

    NotesBoxComponent.h
    Created: 13 Jun 2023 2:54:21am
    Author:  Reda

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class NotesBoxComponent  : public juce::Component
{
public:
    NotesBoxComponent();
    ~NotesBoxComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void logMessage(const juce::String& m);

private:
    juce::TextEditor midiMessagesBox;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NotesBoxComponent)
};
