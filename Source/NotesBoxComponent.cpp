/*
  ==============================================================================

    NotesBoxComponent.cpp
    Created: 13 Jun 2023 2:54:21am
    Author:  Reda

  ==============================================================================
*/

#include <JuceHeader.h>
#include "NotesBoxComponent.h"

//==============================================================================
NotesBoxComponent::NotesBoxComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    addAndMakeVisible(midiMessagesBox);
    midiMessagesBox.setMultiLine(false);

}

NotesBoxComponent::~NotesBoxComponent()
{
}

void NotesBoxComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
}

void NotesBoxComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto r = getLocalBounds().reduced(8);

    midiMessagesBox.setBounds(r.reduced(8));

}

void NotesBoxComponent::logMessage(const juce::String& m)
{
    midiMessagesBox.moveCaretToEnd();
    midiMessagesBox.insertTextAtCaret(m + juce::newLine);
}