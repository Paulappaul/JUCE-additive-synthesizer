#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() : frequency(440), frequency2(240), frequency3(660), frequency4(880), phase(0), waveTableSize(1024), amplitude(0), amplitude2(0), amplitude3(0), amplitude4(0), maxAmplitude(11.0) // constructs with default paramaters - member intializer
{
    setSize(800, 600); // size of the window 


    MainComponent::createFrequencySlider(frequency, Slider1f);
    MainComponent::createAmplitudeSlider(Slider1a);

    MainComponent::createFrequencySlider(frequency2, Slider2f);
    MainComponent::createAmplitudeSlider(Slider2a);


    MainComponent::createFrequencySlider(frequency3, Slider3f);
    MainComponent::createAmplitudeSlider(Slider3a);

    MainComponent::createFrequencySlider(frequency4, Slider4f);
    MainComponent::createAmplitudeSlider(Slider4a);





    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired(juce::RuntimePermissions::recordAudio)
        && !juce::RuntimePermissions::isGranted(juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request(juce::RuntimePermissions::recordAudio,
            [&](bool granted) { setAudioChannels(granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels(0, 2); // no inputs, two outputs
    }
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}



//==============================================================================

void MainComponent::createFrequencySlider(int freqs, juce::Slider* slider) {
    
    slider->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider->setRange(50.0f, 2000, 0.001); // sets frequency Limits
    slider->setValue(freqs); // sets the intial value corroposonding the default constructer. 
    slider->setTextBoxStyle(juce::Slider::TextBoxBelow, true, 200, 40);
    slider->addListener(this);
    addAndMakeVisible(slider); // monitors for changes

}

void MainComponent::createAmplitudeSlider(juce::Slider* slidera) {
    slidera->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slidera->setValue(amplitude * maxAmplitude);
    slidera->setRange(0, maxAmplitude, 0.001);
    slidera->setTextBoxStyle(juce::Slider::TextBoxBelow, true, 200, 40);
    slidera->addListener(this); // monitors for changes
    addAndMakeVisible(slidera);
}



void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    currentSampleRate = sampleRate; // current sample is a global private variable


    for (int i = 0; i < waveTableSize; i++)
    {
        waveTable.insert(i, sin(2.0 * juce::MathConstants<double>::pi * i / waveTableSize)); // draws the sin wave into the array via the insert function see: array in private variable
    }

}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    float* const leftChannel = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample); //  grabs a write pointer at Channel 0 ::  AudioSampleBuffer::getWritePointer(): This returns a pointer to the buffer of float values at a specific sample offset.
    float* const rightChannel = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);

    for (int sample = 0; sample < bufferToFill.numSamples; sample++)
    {
      
        
        float aSampleValue = waveTable[(int)phase] * amplitude;
        float bSampelValue = waveTable[(int)phase2] * amplitude2;
        float cSampelValue = waveTable[(int)phase3] * amplitude3;
        float dSampelValue = waveTable[(int)phase4] * amplitude4;

        phase = fmod((phase + increment), waveTableSize);
        phase2 = fmod((phase2 + increment2), waveTableSize);
        phase3 = fmod((phase3 + increment3), waveTableSize);
        phase4 = fmod((phase4 + increment4), waveTableSize);
       

        leftChannel[sample] = aSampleValue + bSampelValue + cSampelValue + dSampelValue;
        rightChannel[sample] = aSampleValue +  bSampelValue + cSampelValue + dSampelValue;

    }
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

void MainComponent::sliderValueChanged(juce::Slider* slider) //  virtual void; called when a slider value is changed
{
   if (slider == &frequencySlider) // checks first if the slider being changed is the frequency slider
    {
        updateFrequency();
    }

   else if (slider == &frequencySlider2)
    {
        updateFrequency2();
        
    }

   else if (slider == &frequencySlider3)
   {
       updateFrequency3();

   }

   else if (slider == &frequencySlider4)
   {
       updateFrequency4();

   }

    else if (slider == &amplitudeSlider || &amplitudeSlider2 || &amplitudeSlider3 || &amplitudeSlider4) //  checks next if the amplitude slider is being changed. 
    {
        updateAmplitude();
        updateAmplitude2();
        updateAmplitude3();
        updateAmplitude4();
    }

}

// Function that determine what happens when the Slider changes. 

void MainComponent::updateFrequency()

{
    frequency = frequencySlider.getValue(); // returns the value of the slider
    increment = frequency * waveTableSize / currentSampleRate; // smooths the transition

} 

void MainComponent::updateFrequency2()
{

    frequency2 = frequencySlider2.getValue();
    increment2 = frequency2 * waveTableSize / currentSampleRate;

}

void MainComponent::updateFrequency3()
{

    frequency3 = frequencySlider3.getValue();
    increment3 = frequency3 * waveTableSize / currentSampleRate;

}

void MainComponent::updateFrequency4()
{

    frequency4 = frequencySlider4.getValue();
    increment4 = frequency4 * waveTableSize / currentSampleRate;

}

void MainComponent::updateAmplitude()
{
    amplitude = amplitudeSlider.getValue() / maxAmplitude; // returns the amplitude form the respective slider.
}

void MainComponent::updateAmplitude2()
{

    amplitude2 = amplitudeSlider2.getValue() / maxAmplitude;

}

void MainComponent::updateAmplitude3()
{

    amplitude3 = amplitudeSlider3.getValue() / maxAmplitude;

}

void MainComponent::updateAmplitude4()
{

    amplitude4 = amplitudeSlider4.getValue() / maxAmplitude;

}
//==============================================================================
void MainComponent::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    const float border = 50;
    frequencySlider.setBounds(0, border, 200, 200);
    amplitudeSlider.setBounds(200, border, 200, 200);
    frequencySlider2.setBounds(400, border, 200, 200);
    amplitudeSlider2.setBounds(600, border, 200, 200);

    frequencySlider3.setBounds(0, 300, 200, 200);
    amplitudeSlider3.setBounds(200, 300, 200, 200);
    frequencySlider4.setBounds(400, 300, 200, 200);
    amplitudeSlider4.setBounds(600, 300, 200, 200);

}
