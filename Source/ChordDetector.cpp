/*
  ==============================================================================

    ChordDetector.cpp
    Created: 4 Jul 2023 5:54:03pm
    Author:  Reda

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ChordDetector.h"

juce::Array<ChordData> ChordDetector::loadChordDataFromFile()
{
    juce::Array<ChordData> chordsList;

    // Load chord data from JSON file
    juce::File jsonFile(juce::File::getCurrentWorkingDirectory().getParentDirectory().getParentDirectory().getChildFile("chords.json"));
    juce::String jsonString;
    jsonString = jsonFile.loadFileAsString();

    // Parse JSON string
    juce::var jsonData = juce::JSON::parse(jsonString);

    // Check if parsed data is an array
    if (jsonData.isArray())
    {
        // Convert var array to juce::Array
        juce::Array<juce::var>* chordArray = jsonData.getArray();

        
        // Iterate through the chord array
        for (const juce::var& chordVar : *chordArray)
        {
            // Extract chord data from the object
            juce::String name = chordVar["name"].toString();
            juce::String postfix = chordVar["postfix"].toString();
            juce::Array<juce::var> intervalVarArray = chordVar["interval"];
            
            // Convert interval var array to juce::Array<int>
            juce::Array<int> intervalArray;
            for (int i = 0; i < intervalVarArray[0].size(); ++i)
            {
                if (intervalVarArray[0][i].isInt())
                {
                    intervalArray.add(intervalVarArray[0][i]);
                }
            }

            // Create ChordData object and add it to chordsList
            ChordData chordData{ name, postfix, intervalArray };
            chordsList.add(chordData);
        }
    }

    return chordsList;
}


//==============================================================================
ChordDetector::ChordDetector()
{

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
    chordsList = loadChordDataFromFile();
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
