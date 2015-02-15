#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "maxiGrains.h"

class ofApp : public ofBaseApp{
    
public:
    ~ofApp();/* destructor is very useful */
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
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
    
    /* stick you maximilian stuff below */
    
    int		initialBufferSize; /* buffer size */
    int		sampleRate;
    
    double speed;
    double grainLength;
    
    double wave,sample,outputs[2];
    
    ofxMaxiMix myMix;
    ofxMaxiOsc sine1;
    ofxMaxiSample soundFile;
    
    maxiTimestretch<hannWinFunctor> *timeStretcher;

    
    
};
