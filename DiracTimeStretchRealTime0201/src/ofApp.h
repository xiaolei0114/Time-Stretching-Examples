#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "Dirac.h"
#include "MiniAiff.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void audioIn (float * input, int bufferSize, int nChannels); /* output method */
    void audioOut (float * output, int bufferSize, int nChannels); /* input method */
    
    /*************************************** Dirac Objects *************************************/
    
    
    
    /* First we set our time an pitch manipulation values */
    float time; // 115% length
    float pitch; // pitch shift (3 semitones)
    
    int initialBufferSize;
    float sampleRate;
    long numChannels;
    long numFrames;
    long latencyFrames;
    unsigned long inputNumFrames;
    unsigned long inputFramesProcessed = 0; // How many frames we've already processed
    
    
    /* DiracFx Object */
    /* Note that DiracLE supports only one channel! */
    float **audioInBuffer;
    float **audioOutBuffer;
    void *diracFx;
    
    /************************************** Maximillan Objects**********************************/
    double wave,sample,outputs[2]; //sample is the frequency for output
    
    ofxMaxiMix myMix; // Object for Manipulating Sounds
    ofxMaxiSample soundFile;
    
    //maxiTimestretch<hannWinFunctor> *timeStretcher;
    
};
