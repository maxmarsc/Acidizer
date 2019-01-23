/*
  ==============================================================================

    AcidizerParameter.cpp
    Created: 22 Jan 2019 5:30:13pm
    Author:  Max

  ==============================================================================
*/

#include "AcidizerParameter.h"


AcidizerParameter::AcidizerParameter(AcidizerAudioProcessor& p, std::string name, std::string id, int xPos, int yPos) :
	name(name), id(id), xPos(xPos), yPos(yPos)
{
	attachment = std::make_unique<SliderAttachment>(p.treeState, id, knob);
}

AcidizerParameter::~AcidizerParameter()
{
}

void AcidizerParameter::drawName(Graphics& g)
{
	g.setColour(Colours::white);
	g.setFont(15.0f);
	g.drawText(name, 50 + 125 * xPos, 50 + 150 * yPos, 100, 30, Justification::centred);
}

void AcidizerParameter::setupSlider(AcidizerAudioProcessorEditor& gui)
{
	gui.addAndMakeVisible(&knob);
	knob.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	knob.setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
	knob.setPopupDisplayEnabled(true, true, &gui);
}

void AcidizerParameter::resizedCalled()
{
	knob.setBounds(50 + xPos * 125, 80 + yPos * 150, 100, 100);
}
