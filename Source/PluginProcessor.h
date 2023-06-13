/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class JamsterScannerAudioProcessor : public juce::AudioProcessor, public juce::AsyncUpdater, public juce::Button::Listener
{
public:
    //==============================================================================
    JamsterScannerAudioProcessor();
    ~JamsterScannerAudioProcessor();

    //==============================================================================
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    juce::MidiKeyboardState keyboardState;
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(JamsterScannerAudioProcessor)
        juce::Array<juce::MidiMessage> messageLog;

    juce::AudioPlayHead::CurrentPositionInfo info; // The last updated position
    double sampleRate;                       // samples per sec
    int blockSize;                           // samples per block

    int currentSample = 0;
    int currentBeat = 0;
    bool beatFirstHalf = true;
    bool metronomeOn = false;
    bool resetting = false;

    void handleAsyncUpdate() override;
    void buttonClicked(juce::Button*) override;
    void doReset(juce::MidiBuffer&);
};
