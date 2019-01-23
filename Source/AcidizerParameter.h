/*
  ==============================================================================

    A class meant to handle the parameters of the acidizer.
	It manages both GUI placing and displaying, and initialize the attachments
	in order to pass the user's configuration to the audio Processor

  ==============================================================================
*/

#ifndef ACIDIZER_PARAMETER_H
#define ACIDIZER_PARAMETER_H

#pragma once

// Forward Declarations
class AcidizerAudioProcessor;
class AcidizerAudioProcessorEditor;

#include "PluginProcessor.h"

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

class AcidizerParameter
{

public:

	AcidizerParameter::AcidizerParameter(AcidizerAudioProcessor& p, std::string name, std::string id, int xPos, int yPos);
	AcidizerParameter::~AcidizerParameter();

	// Draw the name of the parameter above the slider
	void drawName(Graphics & g);
	// Add the Slider to th GUI and setup its configuration
	void setupSlider(AcidizerAudioProcessorEditor& gui);
	// Called when the main GUI is resized, used to place the parameter once again
	void resizedCalled();

private:

	// Allows the parameter to be linked to the ValueTreeState of the audio processor
	std::unique_ptr<SliderAttachment> attachment;
	// The name of the parameter, display on the GUI
	std::string name;
	// The ID of the parameter, used in the ValueTreeState, must be unique
	std::string id;
	// The slider which allows the user to control the parameters
	Slider knob;
	/*	The relative position of the parameter. As there is six parameters and three columns
		it should be between (0, 0) and (1, 2) */
	int xPos;
	int yPos;
};

#endif // !ACIDIZER_PARAMETER_H