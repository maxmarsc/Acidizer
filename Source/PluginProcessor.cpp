/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"

//==============================================================================
AcidizerAudioProcessor::AcidizerAudioProcessor() :
#ifndef JucePlugin_PreferredChannelConfigurations
	 AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
	),
#endif
	filterOn(true),
	treeState(*this, nullptr, Identifier("AcidizerAPVTS"),
		{
			std::make_unique<AudioParameterFloat>("freq",
													"Cutoff",
													NormalisableRange<float>(20.0f, 
																			12000.0f, 
																			0, 
																			0.25),
													800.0f),
			std::make_unique<AudioParameterFloat>("res",
													"Resonnance",
													1.0f,
													40.0f,
													2.0f),
			std::make_unique<AudioParameterFloat>("volume",
													"Volume",
													0.0f,
													100.0f,
													100.0f),
			std::make_unique<AudioParameterFloat>("drive",
													"Drive",
													0.1f,
													1000.0f,
													100.0f),
			std::make_unique<AudioParameterFloat>("harden",
													"Harden",
													0.0f,
													100.0f,
													50.0f),
			std::make_unique<AudioParameterFloat>("blend",
													"Blend",
													0.0f,
													100.0f,
													100.0f),
			std::make_unique<AudioParameterInt>("choice", 
													"Filter Choice",
													1,
													4,
													1)
		})
{

}

AcidizerAudioProcessor::~AcidizerAudioProcessor()
{
}

//==============================================================================
const String AcidizerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AcidizerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AcidizerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AcidizerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AcidizerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AcidizerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AcidizerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AcidizerAudioProcessor::setCurrentProgram (int index)
{
}

const String AcidizerAudioProcessor::getProgramName (int index)
{
    return {};
}

void AcidizerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void AcidizerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

	// Used to tell the dsp module the current configuration
	dsp::ProcessSpec processSpec;
	processSpec.sampleRate = sampleRate;
	processSpec.maximumBlockSize = samplesPerBlock;
	processSpec.numChannels = getMainBusNumOutputChannels();
	globalSampleRate = sampleRate;

	// We reset the filter in order to avoid any artifact
	filter.reset();

	// We update the filter with the configuration
	updateFilter();
	filter.prepare(processSpec);
}

void AcidizerAudioProcessor::updateFilter()
{
	//We get the values the user choose in the editor
	float freq = *treeState.getRawParameterValue("freq");
	float res = *treeState.getRawParameterValue("res");
	int choice = *treeState.getRawParameterValue("choice");

	switch (choice) {
		case 1:
			filter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
			filterOn = true;
			break;
		case 2:
			filter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::bandPass;
			filterOn = true;
			break;
		case 3:
			filter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::highPass;
			filterOn = true;
			break;
		case 4:
			filterOn = false;
		default:
			break;
	}

	//Update the filter
	filter.state->setCutOffFrequency(globalSampleRate, freq, res/sqrt(2));
}	

void AcidizerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AcidizerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void AcidizerAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

	// ====================== FILTER PART =================================
	filterProcess(buffer);

	// ====================== DISTORTION PART =============================
	distoProcess(buffer, totalNumInputChannels);
	
}

void AcidizerAudioProcessor::filterProcess(AudioBuffer<float>& buffer)
{
	// Filter update
	updateFilter();

	if (filterOn) {
		// Declaring our buffer. No needs to iterate over channels, dsp::AudioBlock points to every channel
		dsp::AudioBlock<float> audioBlock(buffer);
		// Filter processing
		filter.process(dsp::ProcessContextReplacing<float>(audioBlock));
	}
}

void AcidizerAudioProcessor::distoProcess(AudioBuffer<float>& buffer, int totalNumInputChannels)
{
	float drive = *treeState.getRawParameterValue("drive") / 100.0f;
	float blend = *treeState.getRawParameterValue("blend") / 100.0f;
	float volume = *treeState.getRawParameterValue("volume") / 100.0f;
	float harden = *treeState.getRawParameterValue("harden") / 100.0f;

	// Distortion processing
	for (int channel = 0; channel < totalNumInputChannels; ++channel) {
		float* channelBuffer = buffer.getWritePointer(channel);
		for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
			float cleanSignal = channelBuffer[sample];

			float distoredSignal = 2.0 * atan(cleanSignal * drive) / float_Pi;
			distoredSignal = (pow(distoredSignal, 0.5f) * (harden) + pow(distoredSignal, 1.5f) * (1 - harden));
			channelBuffer[sample] = volume * (distoredSignal*blend + cleanSignal * (1.0f - blend)) / 2.0f;
		}
	}
}
//==============================================================================
bool AcidizerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* AcidizerAudioProcessor::createEditor()
{
    return new AcidizerAudioProcessorEditor (*this);
}

//==============================================================================
void AcidizerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

	MemoryOutputStream stream(destData, false);
	treeState.state.writeToStream(stream);
}

void AcidizerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
	ValueTree tree = ValueTree::readFromData(data, sizeInBytes);

	if (tree.isValid()){
		treeState.state = tree;
	}
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AcidizerAudioProcessor();
}
