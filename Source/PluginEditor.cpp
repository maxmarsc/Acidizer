/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"

//==============================================================================
AcidizerAudioProcessorEditor::AcidizerAudioProcessorEditor (AcidizerAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p),
	freqParameter(std::make_unique<AcidizerParameter>(p, "Cutoff", "freq", 0, 0)),
	resParameter(std::make_unique<AcidizerParameter>(p, "Resonance", "res", 1, 0)),
	volumeParameter(std::make_unique<AcidizerParameter>(p, "Volume", "volume", 2, 0)),
	driveParameter(std::make_unique<AcidizerParameter>(p, "Drive", "drive", 0, 1)),
	hardenParameter(std::make_unique<AcidizerParameter>(p, "Hard", "harden", 1, 1)),
	blendParameter(std::make_unique<AcidizerParameter>(p, "Blend", "blend", 2, 1))
{
	freqParameter->setupSlider(*this);
	resParameter->setupSlider(*this);
	volumeParameter->setupSlider(*this);
	driveParameter->setupSlider(*this);
	hardenParameter->setupSlider(*this);
	blendParameter->setupSlider(*this);

	addAndMakeVisible(&filterMenu);
	filterMenu.addItem("Low Pass", 1);
	filterMenu.addItem("Band Pass", 2);
	filterMenu.addItem("High Pass", 3);
	filterMenu.addItem("No Filter", 4);
	filterMenu.setJustificationType(Justification::centred);
	
	filterMenuChoice = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>
		(p.treeState, "choice", filterMenu);

	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(450, 380);
}



AcidizerAudioProcessorEditor::~AcidizerAudioProcessorEditor()
{
}

//==============================================================================
void AcidizerAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

	freqParameter->drawName(g);
	resParameter->drawName(g);
	volumeParameter->drawName(g);
	driveParameter->drawName(g);
	hardenParameter->drawName(g);
	blendParameter->drawName(g);

}

void AcidizerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	freqParameter->resized();
	resParameter->resized();
	volumeParameter->resized();
	driveParameter->resized();
	hardenParameter->resized();
	blendParameter->resized();

	filterMenu.setBounds(175, 15, 100, 25);

}
