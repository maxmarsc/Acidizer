/*
  ==============================================================================

    The audio processing component

	A lot of this code is generated automatically by JUCE when first creating
	an Audio Plugin project

  ==============================================================================
*/

#ifndef PLUGIN_PROCESSOR_H
#define PLUGIN_PROCESSOR_H

#pragma once

#include <string>
#include "../JuceLibraryCode/JuceHeader.h"
#include "AcidizerParameter.h"
#include "PluginEditor.h"


class AcidizerAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    AcidizerAudioProcessor();
    ~AcidizerAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	//=== tree state
	AudioProcessorValueTreeState treeState;

private:
	//The State Variable Filter itself
	dsp::ProcessorDuplicator<dsp::StateVariableFilter::Filter<float>, 
		dsp::StateVariableFilter::Parameters<float>> filter;
	//The global sample rate used by the plugin
	double globalSampleRate;
	// Tells if the user choosed to use the filter or not 
	bool filterOn;

	// Update the filter with the current parameters
	void updateFilter();
	// Process in place the audio transformation of the filter
	void filterProcess(AudioBuffer<float>& buffer);
	// Process in place the audio transformation of the distortion
	void distoProcess(AudioBuffer<float>& buffer, int totalNumInputChannels);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AcidizerAudioProcessor)
};



#endif