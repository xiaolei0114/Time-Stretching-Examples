#pragma once

#include <vector>

#include "ofMain.h"
#include "SoundTouch.h"
#include "WavFile.h"
#include "SoundUtils.h"

using namespace std;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        //void exit();
    
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
    
        void audioIn (float * input, int bufferSize, int nChannels);
        void audioOut (float * input, int bufferSize, int nChannels);
    
        /* SoundTouch Objects*/
        SoundUtils soundUtil;
    
        vector<float> soundOutput; // vector for hold the timestretch result
        double position = 0;
        double soundUpdate();
        float pan;
    
    
    
    
    
    
//        float 	pan;
//        int		sampleRate;
//        bool 	bRingModulation;
//        float 	volume;
//        float   speed;
//        int		bufferSamples;
//    
//        float 	*lAudio;
//        float   *rAudio;
//    
//    //------------------- for the simple sine wave synthesis
//        float 	targetFrequency;
//        float 	phase;
//        float 	phaseAdder;
//        float 	phaseAdderTarget;
//    
//        vector<MiniMaxima> waveForm;
//    
//        WavFile sample; //WinFile is working fine
//    
//        float deltax;
//        float deltapos;
//        float widthPct;
//        bool bScrubMode;
//        bool bReverse;
};
