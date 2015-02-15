#pragma once

#include "ofMain.h"
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
    
    /*************************************** Dirac Objects *************************************/
    
    /* First we set our time an pitch manipulation values */
    float time; // time for stretching, e.g. time = 1.15 = 115% 
    float pitch; // pitch shift (3 semitones)
    
    int initialBufferSize;
    float sampleRate;
    long numChannels;
    long numFrames;
    long latencyFrames;
    unsigned long inputNumFrames;
    unsigned long inputFramesProcessed = 0;
    
    
    /* DiracFx Object */
    /* Note that DiracLE supports only one channel! */
    float **audioInBuffer;
    float **audioOutBuffer;
        
    void *diracFx;
};
