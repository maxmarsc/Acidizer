/*
  ==============================================================================

    AcidizerParameter.h
    Created: 22 Jan 2019 5:30:13pm
    Author:  Max

  ==============================================================================
*/

#ifndef ACIDIZER_PARAMETER_H
#define ACIDIZER_PARAMETER_H

#pragma once

class AcidizerAudioProcessor;
class AcidizerAudioProcessorEditor;

#include "PluginProcessor.h"

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

class AcidizerParameter
{

public:

	AcidizerParameter::AcidizerParameter();

	AcidizerParameter::AcidizerParameter(AcidizerAudioProcessor& p, std::string name, std::string id, int xPos, int yPos);
	AcidizerParameter::~AcidizerParameter();

	void drawName(Graphics & g);
	void setupSlider(AcidizerAudioProcessorEditor& gui);
	void resized();

private:

	std::unique_ptr<SliderAttachment> attachment;
	std::string name;
	std::string id;
	Slider knob;
	int xPos;
	int yPos;

};

#endif // !ACIDIZER_PARAMETER_H