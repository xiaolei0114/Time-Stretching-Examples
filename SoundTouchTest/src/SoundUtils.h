//
//  SoundUtils.h
//  SoundTouchTest
//
//  Created by Zhang Xinlei on 2/7/15.
//
//

#ifndef __SoundTouchTest__SoundUtils__
#define __SoundTouchTest__SoundUtils__

#include <stdio.h>
#include <vector>
#include "ofMain.h"
#include "SoundTouch.h"
#include "WavFile.h"
#endif /* defined(__SoundTouchTest__SoundUtils__) */

using namespace soundtouch;
using namespace std;

class SoundUtils {
    private :
        WavFile soundFile;
        SoundTouch pSoundTouch;
    public :
    
    /**
     * Empty Constructor. Set the SampleRate, Channels, and Bits to be default numbers
     */
    SoundUtils();
    
    /**
     * Constructor with path to the sound file to be read
     * @param inFilePath: Relative path to the sound file to be read. By default the data should be put in the data folder.
     */
    SoundUtils(string inFilePath);
    virtual ~SoundUtils();
    
    
    /**
     * Read a .wav File by its relative address to ../SoundTouchTest using WavFile class methods: WavFile.load(tmpPath);
     * Key parameters are SampleRate, Channels, and Bits per sample.
     * @param inFilePath  Path of the input file stored in data folder
     * 
     * Test AC.
    */
    bool loadWavFile(const string inFilePath);
    
    /**
     * Setup SoundTouch to change tempo and/or sample rate.
     * Currently not deal with
     * @param outTempChange: the tempo change in percentage compared to the original one.
     *                       Range [-50, 100], which means tempo reduced by (-50 .. +100)%
     * @param outSampleRate: the desired output sample rate, in case the output SampleRate is different from the output one
     *
     * Test AC.
     */
    bool setupSoundTouch(float outTempoChange, int outSampleRate);
    
    /**
     * TimeStretching the WavFile read in real time. Try to use the sample: myData read in WavFile as input source
     * 
     *
     *
     */
    int tempoProcess(vector<float> &outputSample);
    
    /**
     * Modify the Pitch of the WavFile read in real time.
     *
     *
     *
     */
    int pitchProcess();
    
    /**
     * Process the Wav Sample Read to trim out the empty space in sample read.
     *
     *
     *
     */
    int trimEmptySamples();
};