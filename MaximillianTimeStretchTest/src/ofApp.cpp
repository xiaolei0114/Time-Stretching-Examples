/* This is an example of how to integrate maximilain into openFrameworks,
 including using audio received for input and audio requested for output.
 
 
 You can copy and paste this and use it as a starting example.
 
 */


#include "ofApp.h"



//-------------------------------------------------------------
ofApp::~ofApp() {
    
}


//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    ofSetVerticalSync(true);
    
    /* This is stuff you always need.*/
    
    sampleRate 			= 44100; /* Sampling Rate */
    initialBufferSize	= 8192;	/* Buffer Size. you have to fill this buffer with sound*/
    
    speed = 1;
    grainLength = 0.05;
    
    timeStretcher = new maxiTimestretch<hannWinFunctor> (&soundFile);
    
    //beat.load(ofToDataPath("beat2.wav"));
    soundFile.load(ofToDataPath("sound/sheldon_1.wav"));
    //soundFile.load(ofToDataPath("sound/paris.wav"));
    soundFile.getLength();//print out the length to the console
    
    ofxMaxiSettings::setup(sampleRate, 2, initialBufferSize);
    ofSoundStreamSetup(2,0,this, sampleRate, initialBufferSize, 4);/* Call this last ! */
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    /* You can use any of the data from audio received and audiorequested to draw stuff here.
     Importantly, most people just use the input and output arrays defined above.
     Clever people don't do this. This bit of code shows that by default, each signal is going to flip
     between -1 and 1. You need to account for this somehow. Get the absolute value for example.
     */
    
    ofSetColor(255, 255, 255,255);
    ofRect(600, 300, sample*150, sample*150); /* audio sigs go between -1 and 1. See?*/
    ofCircle(200, 300, wave*150);
    
}

//--------------------------------------------------------------
void ofApp::audioOut (float * output, int bufferSize, int nChannels){
    
    for (int i = 0; i < bufferSize; i++){
        
        float wave = timeStretcher->play(speed, grainLength, 2, 0);
        //play result
        myMix.stereo(wave, outputs, 0.5);
        
        output[i*nChannels    ] = outputs[0]; /* You may end up with lots of outputs. add them here */
        output[i*nChannels + 1] = outputs[1];
    }
    
}

//--------------------------------------------------------------
void ofApp::audioIn (float * input, int bufferSize, int nChannels){
    
    
    /* You can just grab this input and stick it in a double, then use it above to create output*/
    
    for (int i = 0; i < bufferSize; i++){
        
        /* you can also grab the data out of the arrays*/
        
        
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
    speed = ((double ) x / ofGetWidth() * 4.0) - 2.0;
    printf("The speed is %.2f\n", speed);
    grainLength = ((double) y / ofGetHeight() * 0.1) + 0.001;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}



//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}