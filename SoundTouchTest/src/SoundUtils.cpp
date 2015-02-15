//
//  SoundUtils.cpp
//  SoundTouchTest
//
//  Created by Zhang Xinlei on 2/7/15.
//
//

#include "SoundUtils.h"
#include "WavFile.h"
// Processing chunk size (size chosen to be divisible by 2, 4, 6, 8, 10, 12, 14, 16 channels ...)
#define BUFF_SIZE           6720


// Handy function: Add elements to a vector from an array
int addFromArray(vector<float> &sample, float *array, int maxElem) {
    
    int i;
    for (i = 0; i< maxElem;i++)
    {
        sample.push_back(array[i]);
    }
    //
    if (i == maxElem) return maxElem;
    else return i;
}

//Empty constructor
SoundUtils::SoundUtils() {
    //printf("SoundUtils constructor is working !\n");
}

SoundUtils::SoundUtils(string inFilePath) {
    soundFile.load(inFilePath);
}


SoundUtils::~SoundUtils() {
    
}

bool SoundUtils::loadWavFile(const string inFilePath)
{
    if (!soundFile.load(inFilePath)) return false;
    else {
        printf("Sound File load Successfully:\n %s", soundFile.getSummary());
        return true;
    }
    
}

bool SoundUtils::setupSoundTouch(float outTempoChange, int outSampleRate)
{
    int inSampleRate;
    int inChannels;
    
    //get sampleRate and channel numbers from input
    inSampleRate = (int)soundFile.getSampleRate();
    inChannels = (int)soundFile.getNumChannels();
    
    //Set the soundtouch object for these 2 params
    pSoundTouch.setSampleRate(inSampleRate);
    pSoundTouch.setChannels(inChannels);
    
    //Set the desired speed (Currently don't deal with pitch and rath)
    pSoundTouch.setTempoChange(outTempoChange);
    
    //Settings for Tune algorithm for speech processing.(default is for music)
    pSoundTouch.setSetting(SETTING_SEQUENCE_MS, 40);
    pSoundTouch.setSetting(SETTING_SEEKWINDOW_MS, 15);
    pSoundTouch.setSetting(SETTING_OVERLAP_MS, 8);
    
    //In case other sampleRate other than the input ones are desired.
    //modifies the outputRate
    if (inSampleRate!= outSampleRate)
        pSoundTouch.setRate((float)inSampleRate / (float)outSampleRate);
    
    printf("Setup for Sound Touch Completed Succcessfully !\n");
}

int SoundUtils::tempoProcess(vector<float> &outputSample)
{
    int nSamples; //number of samples read to the sampleBuffer for a processing round.
    int nChannels;
    int nBuffSizeSamples; //sample numbers the sampleBuffer can hold according to BUFF_SIZE and nChannels.
    float sampleBuffer[BUFF_SIZE]; // used to hold proceeded results outputed each round by the pipeline, SAMPLETYPE is float, BUFF_SIZE is 6720
    
    nChannels = (int)soundFile.getNumChannels(); // get channel numbers from inFile
    assert(nChannels > 0); // 0 Channel will break the program.
    nBuffSizeSamples = BUFF_SIZE / nChannels;

//    //get the absolute path of the path user specified.
//    string myPath = ofToDataPath(soundFile.getPath(),true).c_str();
//    
//    //setup the iostream to read a binary file
//    ifstream inFile( myPath.c_str(), ios::in | ios::binary);
//    ofLog(OF_LOG_NOTICE, "Reading file %s",myPath.c_str());
//    
//    if(!inFile.is_open())
//    {
//        ofLog(OF_LOG_ERROR,"Error opening file. File not loaded.");
//        return 0;
//    }
    
    int numSampleProceeded = 0;
    
    // Get the numbers of total Samples in source file.
    int bytePerSample = soundFile.getBitsPerSample()/8;
    int totalSamples = soundFile.getDataSize() / bytePerSample;
    
    // Number of sound Elements to be proceeded.
    nSamples = totalSamples/nChannels;
    
    // Process samples
    {
        // Put all the elements to be proceeded to the Audio Processor
        // Currently, soundFile.myData is the data source for processing. 
        pSoundTouch.putSamples((float *)soundFile.myData, nSamples);
        
        do
        {
            // Because each time all the elements read from the receiveSamples() will be copied to outputBuffer
            // So there should be no worries about its elements be covered by new proceeded elements from receiveSamples.
            nSamples = pSoundTouch.receiveSamples(sampleBuffer, nBuffSizeSamples);
            numSampleProceeded += nSamples;
            
            // Write to the final output result buffer.
            // In total nSamples * nChannels
            addFromArray(outputSample,sampleBuffer,nSamples * nChannels);
            
            
        } while (nSamples != 0);
    }
    
    pSoundTouch.flush();
    do
    {
        nSamples = pSoundTouch.receiveSamples(sampleBuffer, nBuffSizeSamples);
        numSampleProceeded += nSamples;
        
        // Write to the output buffer
        addFromArray(outputSample,sampleBuffer,nSamples * nChannels);
        
    } while (nSamples != 0);
    
    return numSampleProceeded;
}




