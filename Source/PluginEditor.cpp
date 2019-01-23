/*
  ==============================================================================

    The main GUI component

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
	/*	We let the parameters set themselves up on the UI according to their parameters */
	freqParameter->setupSlider(*this);
	resParameter->setupSlider(*this);
	volumeParameter->setupSlider(*this);
	driveParameter->setupSlider(*this);
	hardenParameter->setupSlider(*this);
	blendParameter->setupSlider(*this);

	/*  We setup the filter menu directly in here, as it is the only ComboBox of the plugin*/
	addAndMakeVisible(&filterMenu);
	filterMenu.addItem("Low Pass", 1);
	filterMenu.addItem("Band Pass", 2);
	filterMenu.addItem("High Pass", 3);
	filterMenu.addItem("No Filter", 4);
	filterMenu.setJustificationType(Justification::centred);
	
	/*  We declare the ComboBox attachment */
	filterMenuChoice = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>
		(p.treeState, "choice", filterMenu);

	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(450, 380);
}



AcidizerAudioProcessorEditor::~AcidizerAudioProcessorEditor()
{
	//Nothing to do here
}

//==============================================================================
void AcidizerAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

	// We tell the parameter to draw their name above them
	freqParameter->drawName(g);
	resParameter->drawName(g);
	volumeParameter->drawName(g);
	driveParameter->drawName(g);
	hardenParameter->drawName(g);
	blendParameter->drawName(g);

}

void AcidizerAudioProcessorEditor::resized()
{
	/*	The plugin is not really meant to be resized.
		For now, if the user resize it, nothing moves dynamically.
		Could be changed in the near future, but it is not really interesting to do. */
    
	// The parameters set themselves as usual
	freqParameter->resizedCalled();
	resParameter->resizedCalled();
	volumeParameter->resizedCalled();
	driveParameter->resizedCalled();
	hardenParameter->resizedCalled();
	blendParameter->resizedCalled();

	filterMenu.setBounds(175, 15, 100, 25);
}
