#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent,
                       public juce::Slider::Listener
{
public:

    //==============================================================================
    MainComponent();

    ~MainComponent() override;
    

    //==============================================================================
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    void createFrequencySlider(int freqs, juce::Slider* slider);
    void createAmplitudeSlider(juce::Slider* slidera);

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override ;



    

private:
    //==============================================================================
    // Your private member variables go here...
    juce::Slider frequencySlider, amplitudeSlider, frequencySlider2, amplitudeSlider2, frequencySlider3, amplitudeSlider3, frequencySlider4, amplitudeSlider4;
    juce::Label frequencyLabel, amplitudeLabel;

    juce::Slider* Slider1f = &frequencySlider;
    juce::Slider* Slider2f = &frequencySlider2;
    juce::Slider* Slider1a = &amplitudeSlider;
    juce::Slider* Slider2a = &amplitudeSlider2;

    juce::Slider* Slider3f = &frequencySlider3;
    juce::Slider* Slider4f = &frequencySlider4;
    juce::Slider* Slider3a = &amplitudeSlider3;
    juce::Slider* Slider4a = &amplitudeSlider4;


    juce::Array<float> waveTable;


    double waveTableSize;

    float frequency;
    float frequency2;
    float frequency3;
    float frequency4;
   
    double increment;
    double increment2;
    double increment3;
    double increment4;
  
    float currentSampleRate;
    

    double phase;
    double phase2;
    double phase3;
    double phase4;

    float amplitude;
    float amplitude2;
    float amplitude3;
    float amplitude4;

    double maxAmplitude;
   


    void sliderValueChanged(juce::Slider* slider) override;
    void updateFrequency();
    void updateFrequency2();
    void updateFrequency3();
    void updateFrequency4();
    void updateAmplitude();
    void updateAmplitude2();
    void updateAmplitude3();
    void updateAmplitude4();


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
