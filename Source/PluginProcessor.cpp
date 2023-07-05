/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "JucePluginDefines.h"

//==============================================================================
JamsterScannerAudioProcessor::JamsterScannerAudioProcessor()
    #ifndef JucePlugin_PreferredChannelConfigurations
      : AudioProcessor (BusesProperties()
        #if ! JucePlugin_IsMidiEffect
          #if ! JucePlugin_IsSynth
            .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
          #endif
          .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
        #endif
      )
    #endif
{
}

JamsterScannerAudioProcessor::~JamsterScannerAudioProcessor()
{
}

//==============================================================================
const juce::String JamsterScannerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool JamsterScannerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JamsterScannerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JamsterScannerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double JamsterScannerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JamsterScannerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int JamsterScannerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JamsterScannerAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String JamsterScannerAudioProcessor::getProgramName (int index)
{
    return {};
}

void JamsterScannerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void JamsterScannerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    inputKeyboardState.reset();
    outputKeyboardState.reset();
    reset();
}

void JamsterScannerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    inputKeyboardState.reset();
    outputKeyboardState.reset();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JamsterScannerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void JamsterScannerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi)
{   
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());


    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
    }
    /*
    if (midi.isEmpty()) {
        return;
    }
    */
    inputKeyboardState.processNextMidiBuffer(midi, 0, buffer.getNumSamples(), true);

    bool update = false;
    
    // Get incomming midi messages and log them
    int ignore;
    for (juce::MidiBuffer::Iterator it(midi); it.getNextEvent(inputMsg, ignore);)
    {
        outputMsg = inputMsg;
        outputMsg.setNoteNumber(inputMsg.getNoteNumber() + (octTransposeValue * 12) + stTransposeValue);

        if (inputMsg.isNoteOnOrOff()) {
            if (inputMsg.isNoteOn()) {
                inputMessageLog.add(inputMsg.getNoteNumber());
                outputMessageLog.add(outputMsg.getNoteNumber());
            }
            else if (inputMsg.isNoteOff()) {
                inputMessageLog.remove(inputMessageLog.indexOf(inputMsg.getNoteNumber()));
                outputMessageLog.remove(outputMessageLog.indexOf(outputMsg.getNoteNumber()));
            }
            triggerAsyncUpdate();
            outputMidiBuffer.addEvent(outputMsg, outputMidiBuffer.getNumEvents() - 1);
        }
    }

    outputKeyboardState.processNextMidiBuffer(outputMidiBuffer, 0, buffer.getNumSamples(), true);
    /*
    for (int deviceIndex = 0; deviceIndex < juce::MidiOutput::getAvailableDevices().size(); ++deviceIndex)
    {
        midiOutputDevice = juce::MidiOutput::openDevice(deviceIndex);
        midiOutputDevice->sendBlockOfMessagesNow(outputMidiBuffer);
    }
    */
    midi.clear();
    outputMidiBuffer.clear();
}

//==============================================================================
bool JamsterScannerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* JamsterScannerAudioProcessor::createEditor()
{
    JamsterScannerAudioProcessorEditor *editor = new JamsterScannerAudioProcessorEditor(*this);
    return editor;
}

//==============================================================================
void JamsterScannerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void JamsterScannerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void JamsterScannerAudioProcessor::setOctTransposeValue(int transposeValue)
{
    octTransposeValue = transposeValue;
}

void JamsterScannerAudioProcessor::setStTransposeValue(int transposeValue)
{
    stTransposeValue = transposeValue;
}

void JamsterScannerAudioProcessor::sliderChanged()
{
    outputKeyboardState.allNotesOff(0);
    outputMessageLog.clear();
    triggerAsyncUpdate();
}


void JamsterScannerAudioProcessor::handleAsyncUpdate()
{   
    JamsterScannerAudioProcessorEditor *editor =
        dynamic_cast<JamsterScannerAudioProcessorEditor*>(getActiveEditor());

    if (editor) {
        editor->clearInputNotes();
        editor->clearInputChord();
        for (int* cur = inputMessageLog.begin(); cur < inputMessageLog.end(); cur++) {
            editor->logInputNotes(*cur);            
        }
        editor->logInputChord(inputMessageLog);
        editor->clearOutputNotes();
        for (int* cur = outputMessageLog.begin(); cur < outputMessageLog.end(); cur++) {
            editor->logOutputNotes(*cur);
        }
    }
}



//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JamsterScannerAudioProcessor();
}
