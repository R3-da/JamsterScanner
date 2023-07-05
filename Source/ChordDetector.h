/*
  ==============================================================================

    ChordDetector.h
    Created: 4 Jul 2023 5:54:03pm
    Author:  Reda

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

struct NoteInterval
{
    int note;
    int interval;
};

struct ChordData
{
    juce::String name;
    juce::String postfix;
    juce::Array<int> interval;
};

struct ChordIndexStartpoint
{
    int index;
    int startpoint;
};

//==============================================================================
/*
*/
class ChordDetector  : public juce::Component
{
public:
    ChordDetector();
    ~ChordDetector() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    static juce::Array<ChordData> loadChordDataFromFile();

    int getNoteIndex(int noteNum);

    juce::Array<NoteInterval> getNotesIntervals(juce::Array<int> inputMessageLog);
    int getChordIndexByInterval(const juce::Array<int>& interval);
    juce::Array<ChordIndexStartpoint> getChordsIndexStartPoint(juce::Array<int> inputMessageLog);

    juce::Array<ChordData> chordsList;
    juce::Array<ChordIndexStartpoint> chordIndexStartpoint;

    int notesPerOctave = 12;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChordDetector)
};
