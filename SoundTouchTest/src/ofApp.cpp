#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    soundUtil.loadWavFile("sheldon_1.wav");
    soundUtil.setupSoundTouch(-10.0, 44100);
    soundUtil.tempoProcess(soundOutput);
    
    ofSoundStreamSetup(2, 0, this, 44100, 8192, 4);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
}

//--------------------------------------------------------------
void ofApp::audioOut (float * output, int bufferSize, int nChannels){
    float leftScale = 1 - pan;
    float rightScale = pan;
    
    for (int i = 0; i < bufferSize; i++){
//            // mono
//            if(sample.getChannels() == 1) {
//                float smp = sample.update();
//                output[i*nChannels    ] = leftScale;
//                output[i*nChannels + 1] = rightScale;
//            }
            // stereo
//            else if (sample.getChannels() == 2) {
                output[i*nChannels    ] = soundUpdate() * leftScale;
                output[i*nChannels + 1] = soundUpdate() * rightScale;
//            }
//            else
//            {
//                output[i*nChannels    ] = 0.0;
//                output[i*nChannels + 1] = 0.0;
//            }
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
    int width = ofGetWidth();
    pan = (float)x / (float)width;
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

double ofApp::soundUpdate()
{
    
//    long length=getLength();
    double remainder;
    position=(position+1);
    remainder = position - (long) position;
    
//    // check if reached EOF.
//    // If it is and it's under looping mode, then reset position, else stop playing it.
//    if ((long) position>length) {
//        if(getIsLooping()) {
//            position=0;
//        }
//        else {
//            soundStatus &= ~PLAYING;
//            return 0;
//        }
//    }
//    
//    //check if position less than zero (reverse)
//    if ((long) position < 0) {
//        if(getIsLooping()) {
//            position = length;
//        }
//        else {
//            soundStatus &= ~PLAYING;
//            return 0;
//        }
//    }
    
    // It is by updating this output sample data to the outer audioOut's output[] to generate sounds.
    return ( (double) ((1.0-remainder) * soundOutput[1+ (long) position] + remainder * soundOutput[2+(long) position])/32767.0 );//linear interpolation
    
}







//#include "ofApp.h"
//
////--------------------------------------------------------------
//void ofApp::setup(){
//    ofBackground(255,255,255);
//    ofSetFrameRate(30);
//    
//    sampleRate 			= 44100;
//    phase 				= 0;
//    phaseAdder 			= 0.0f;
//    phaseAdderTarget 	= 0.0f;
//    volume				= 1.0f;
//    bRingModulation 	= false;
//    lAudio = new float[256];
//    rAudio = new float[256];
//    
//    sample.load("sheldon_1.wav"); // supports mono or stereo .wav files
//    sample.setLooping(true);
//    sample.play();
//    
//    sample.generateWaveForm(&waveForm);
//    sample.getPausePostionPairs();
//    
//    bScrubMode = false;
//    bReverse = false;
//    
//    targetFrequency = 1000.0f;
//    phaseAdderTarget = (targetFrequency / (float) sampleRate) * TWO_PI;
//    
//    
//    ofSoundStreamSetup(2, 0, this, sampleRate, 256, 4);
//}
//
////--------------------------------------------------------------
//void ofApp::exit(){
//    ofSoundStreamStop();
//    ofSoundStreamClose();
//    delete lAudio;
//    delete rAudio;
//    
//}
////--------------------------------------------------------------
//void ofApp::update(){
//    
//    static int last_x = 0;
//    static int curr_x = 0;
//    
//    last_x = curr_x;
//    curr_x = mouseX;
//    deltax = (1.0f + fabs(curr_x - last_x))/1.0f;
//    
//    if(bScrubMode) {
//        float next_pos = widthPct;
//        float curr_pos = sample.getPosition();
//        
//        deltapos = (next_pos - curr_pos);
//        
//        speed = deltapos*((float)sample.getLength()/(float)sample.getSampleRate())*10.0f;
//        sample.setSpeed(speed);
//    }
//    
//}
//
////--------------------------------------------------------------
//void ofApp::draw(){
//    
//    // draw waveform
//    sample.drawWaveForm(5, 500, ofGetWidth()-10, 100, &waveForm);
//    
//    // draw the left blank:
//    ofSetHexColor(0x333333);
//    ofRect(100,100,256,200);
//    ofSetHexColor(0xFFFFFF);
//    for (int i = 0; i < 256; i++){
//        ofLine(100+i,200,100+i,200+lAudio[i]*200.0f);
//    }
//    
//    // draw the right blank:
//    ofSetHexColor(0x333333);
//    ofRect(600,100,256,200);
//    ofSetHexColor(0xFFFFFF);
//    for (int i = 0; i < 256; i++){
//        ofLine(600+i,200,600+i,200+rAudio[i]*200.0f);
//    }
//    
//    
//    ofSetHexColor(0x333333);
//    char reportString[255];
//    sprintf(reportString, "volume: (%f) modify with -/+ keys\npan: (%f)\nspeed: (%f)\nplayback: %s\nposition: %f\npaused: %s", volume, pan, speed, bRingModulation ? "ring modulation" : "normal",sample.getPosition(),sample.getIsPaused()?"yes":"no");
//    if (bRingModulation) sprintf(reportString, "%s (%fhz)", reportString, targetFrequency);
//    
//    ofDrawBitmapString(reportString,80,380);
//    
//    ofDrawBitmapString("Items: " + ofToString(sample.getLength()), 450, 379);
//    ofDrawBitmapString("Position: " + ofToString(sample.getPosition()), 450, 430);
//    
//    ofDrawBitmapString("Total Time: " + ofToString(sample.getLength()/sample.getChannels()/sample.getSampleRate()) + " s", 450, 400);
//    ofDrawBitmapString("Current time: " + ofToString(sample.getPosition()* (sample.getLength()/sample.getChannels()/sample.getSampleRate())) + " s", 450, 460);
//}
//
//
////--------------------------------------------------------------
//void ofApp::keyPressed  (int key){
//    static bool toggle = false;
//    
//    if (key == '-'){
//        volume -= 0.05;
//        volume = MAX(volume, 0);
//    } else if (key == '+'){
//        volume += 0.05;
//        volume = MIN(volume, 1);
//    }
//    
//    if(key == ' ')
//    {
//        toggle = !toggle;
//        sample.setPaused(toggle);
//    }
//    
//    if(key == 'r')
//    {
//        bReverse = !bReverse;
//        if(bReverse) {
//            speed = -1.0f;
//            sample.setSpeed(speed);
//        }
//        else
//        {
//            speed = 1.0f;
//            sample.setSpeed(speed);
//        }
//    }
//    
//    if(key == 's')
//    {
//        if(bScrubMode) {speed = 1.0f;sample.setSpeed(speed);}
//        bScrubMode = !bScrubMode;
//    }
//    
//    if(key == 'h')
//    {
//        sample.stop();
//    }
//    if(key == 'p')
//    {
//        sample.play();
//    }
//}
//
////--------------------------------------------------------------
//void ofApp::keyReleased  (int key){
//    
//}
//
////--------------------------------------------------------------
//void ofApp::mouseMoved(int x, int y ){
//    
//    int width = ofGetWidth();
//    widthPct = (float)x / (float)width;
//    pan = widthPct;
//    
//    float height = (float)ofGetHeight();
//    float heightPct = 1 - ((height-y) / height);
//    
//    if(!bScrubMode) {
//        speed = 2*(-1.0f + 2*heightPct);
//        sample.setSpeed(speed);
//    }
//    
//    
//}
//
////--------------------------------------------------------------
//void ofApp::mouseDragged(int x, int y, int button){
//    int width = ofGetWidth();
//    pan = (float)x / (float)width;
//    
//    float height = (float)ofGetHeight();
//    float heightPct = ((height-y) / height);
//    targetFrequency = 2000.0f * heightPct;
//    phaseAdderTarget = (targetFrequency / (float) sampleRate) * TWO_PI;
//}
//
////--------------------------------------------------------------
//void ofApp::mousePressed(int x, int y, int button){
//    bRingModulation = true;
//}
//
//
////--------------------------------------------------------------
//void ofApp::mouseReleased(int x, int y, int button){
//    bRingModulation = false;
//}
//
////--------------------------------------------------------------
//void ofApp::windowResized(int w, int h){
//    
//}
////--------------------------------------------------------------
//void ofApp::audioOut(float * output, int bufferSize, int nChannels){
//    
//    float leftScale = 1 - pan;
//    float rightScale = pan;
//    
//    // sin (n) seems to have trouble when n is very large, so we
//    // keep phase in the range of 0-TWO_PI like this:
//    while (phase > TWO_PI){
//        phase -= TWO_PI;
//    }
//    
//    phaseAdder = 0.95f * phaseAdder + 0.05f * phaseAdderTarget;
//    
//    for (int i = 0; i < bufferSize; i++){
//        if ( bRingModulation == true)
//        {
//            phase += phaseAdder;
//            float mod = sin(phase);
//            
//            // mono
//            if(sample.getChannels() == 1) {
//                float smp = sample.update();
//                lAudio[i] = output[i*nChannels    ] = mod * smp * volume * leftScale;
//                rAudio[i] = output[i*nChannels + 1] = mod * smp * volume * rightScale;
//            }
//            // stereo
//            else if (sample.getChannels() == 2) {
//                lAudio[i] = output[i*nChannels    ] = mod * sample.update() * volume * leftScale;
//                rAudio[i] = output[i*nChannels + 1] = mod * sample.update() * volume * rightScale;
//            }
//        }
//        else //normal playback
//        {
//            // mono
//            if(sample.getChannels() == 1) {
//                float smp = sample.update();
//                lAudio[i] = output[i*nChannels    ] = smp * volume * leftScale;
//                rAudio[i] = output[i*nChannels + 1] = smp * volume * rightScale;
//            }
//            // stereo
//            else if (sample.getChannels() == 2) {
//                lAudio[i] = output[i*nChannels    ] = sample.update() * volume * leftScale;
//                rAudio[i] = output[i*nChannels + 1] = sample.update() * volume * rightScale;
//            }
//            else
//            {
//                lAudio[i]  = output[i*nChannels    ] = 0.0;
//                rAudio[i]  = output[i*nChannels + 1] = 0.0;
//            }
//        }
//        
//        
//    }
//}
//
////--------------------------------------------------------------
//void ofApp::gotMessage(ofMessage msg){
//    
//}
//
////--------------------------------------------------------------
//void ofApp::dragEvent(ofDragInfo dragInfo){
//    
//}
