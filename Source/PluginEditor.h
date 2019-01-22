/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGIN_EDITOR_H
#define PLUGIN_EDITOR_H


#pragma once


class AcidizerParameter;

#include "PluginProcessor.h"




//==============================================================================
/**
*/
class AcidizerAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    AcidizerAudioProcessorEditor (AcidizerAudioProcessor&);
    ~AcidizerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AcidizerAudioProcessor& processor;

	std::unique_ptr<AcidizerParameter> freqParameter;
	std::unique_ptr<AcidizerParameter> resParameter;
	std::unique_ptr<AcidizerParameter> volumeParameter;
	std::unique_ptr<AcidizerParameter> driveParameter;
	std::unique_ptr<AcidizerParameter> hardenParameter;
	std::unique_ptr<AcidizerParameter> blendParameter;

	ComboBox filterMenu;
	std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> filterMenuChoice;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AcidizerAudioProcessorEditor)
    
};

#endif // !PLUGIN_EDITOR_H