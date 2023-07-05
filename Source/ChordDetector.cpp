/*
  ==============================================================================

    ChordDetector.cpp
    Created: 4 Jul 2023 5:54:03pm
    Author:  Reda

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ChordDetector.h"




//==============================================================================
ChordDetector::ChordDetector()
{
    chordsList.add({ "powerchord", "5", { 7, 5 } });
    chordsList.add({ "major", "", { 4, 3, 5 } });
    chordsList.add({ "minor", "m", { 3, 4, 5 } });
    chordsList.add({ "augmented", "aug", { 4, 4, 4 } });
    chordsList.add({ "diminished", "dim", { 3, 3, 6 } });
    chordsList.add({ "suspended", "sus2", { 2, 5, 5 } });
    chordsList.add({ "suspended", "sus4", { 5, 2, 5 } });
    chordsList.add({ "7major(short)", "7maj", { 7, 4, 1 } });
    chordsList.add({ "7(short)", "7", { 7, 3, 2 } });
    chordsList.add({ "6major", "6maj", { 4, 3, 2, 3 } });
    chordsList.add({ "6minor", "6min", { 3, 4, 2, 3 } });
    chordsList.add({ "7diminished", "7dim", { 3, 3, 3, 3 } });
    chordsList.add({ "7major", "7maj", { 4, 3, 4, 1 } });
    chordsList.add({ "7minor", "7min", { 3, 4, 3, 2 } });
    chordsList.add({ "7augmented", "7aug", { 4, 4, 2, 2 } });
    chordsList.add({ "7half-diminished", "7hdim", { 3, 3, 4, 2 } });
    chordsList.add({ "7dominant", "7dom", { 4, 3, 3, 2 } });
    chordsList.add({ "7minor-major", "7minmaj", { 3, 4, 4, 1 } });
    chordsList.add({ "7augmented-major", "7augmaj", { 4, 4, 3, 1 } });
    chordsList.add({ "9add", "9add", { 2, 2, 3, 5 } });
    chordsList.add({ "9", "9", { 2, 2, 3, 3, 2 } });
    chordsList.add({ "9minor", "9min", { 2, 1, 4, 3, 2 } });
    chordsList.add({ "9major", "9maj", { 2, 2, 3, 4, 1 } });
    chordsList.add({ "b9", "9-", { 1, 3, 3, 3, 2 } });
    chordsList.add({ "#9", "9+", { 3, 1, 3, 3, 2 } });
    chordsList.add({ "11(short)", "11", { 4, 1, 2, 3, 2 } });
    chordsList.add({ "11", "11", { 2, 2, 1, 2, 3, 2 } });
    chordsList.add({ "13(short)", "13", { 4, 3, 2, 1, 2 } });
    chordsList.add({ "13", "13", { 2, 2, 1, 2, 2, 1, 2 } });
}

ChordDetector::~ChordDetector()
{
}

void ChordDetector::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

}

void ChordDetector::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

int ChordDetector::getNoteIndex(int noteNum)
{
    return noteNum%notesPerOctave;
}

juce::Array<NoteInterval> ChordDetector::getNotesIntervals(juce::Array<int> inputMessageLog)
{

    juce::Array<int> uniqueNotes;
    for (int noteNum : inputMessageLog)
    {
        int noteIndex = getNoteIndex(noteNum);
        if (!uniqueNotes.contains(noteIndex))
            uniqueNotes.add(noteIndex);
    }

    uniqueNotes.sort();

    juce::Array<NoteInterval> intervals;
    for (int i = 0; i < uniqueNotes.size(); ++i)
    {
        int nextIndex = (i + 1) % uniqueNotes.size();
        int interval = (i == uniqueNotes.size() - 1) ? uniqueNotes[0] + notesPerOctave - uniqueNotes[i] :
            uniqueNotes[nextIndex] - uniqueNotes[i];
        intervals.add({ uniqueNotes[i], interval });
    }

    return intervals;
}

int ChordDetector::getChordIndexByInterval(const juce::Array<int>& interval)
{
    for (int i = 0; i < chordsList.size(); ++i)
    {
        const ChordData& chord = chordsList[i];
        if (chord.interval == interval)
        {
            return i;
        }
    }

    return -1;
}

juce::Array<ChordIndexStartpoint> ChordDetector::getChordsIndexStartPoint(juce::Array<int> inputMessageLog)
{
    juce::Array<NoteInterval> notesIntervals = getNotesIntervals(inputMessageLog);
    
    juce::Array<int> notes;
    juce::Array<int> interval;
    for (const NoteInterval& noteInterval : notesIntervals)
    {
        
        notes.add(noteInterval.note);
        interval.add(noteInterval.interval);
    }

    juce::Array<ChordIndexStartpoint> chordsIndexStartPointList;
    for (int i = 0; i < interval.size(); ++i)
    {
        juce::Array<int> currentInterval;
        currentInterval.addArray(interval, i, interval.size() - i);
        currentInterval.addArray(interval, 0, i);
        int currentIntervalIndex = getChordIndexByInterval(currentInterval);
        if (currentIntervalIndex != -1)
        {
            chordsIndexStartPointList.add({ currentIntervalIndex, notes[i] });
        }
    }
    return chordsIndexStartPointList;
}
