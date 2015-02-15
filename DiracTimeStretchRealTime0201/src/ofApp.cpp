#include "ofApp.h"

//Input file and Output file for audio processing
char infileNameWithPath[] = "/Users/ZhangXinlei/Programming/openFrameworks/of_v0.8.1_osx_release/apps/Voice Processing/DiracTimeStretchRealTime0201/test.aif";
char outfileNameWithPath[] = "/Users/ZhangXinlei/Programming/openFrameworks/of_v0.8.1_osx_release/apps/Voice Processing/DiracTimeStretchRealTime0201/out.aiff";

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    
    /************************************ Public Settings for both MaxiMillian & Dirac3 LE *****************************************************/
    /******************************************************************************************************************************************/
    
    sampleRate = 44100;
    numChannels = 1;// Dirac 3LE Supports only 1 channel currently
    initialBufferSize = 8192;

    /******************************************************* Settings for MaxiMillian *********************************************************/
    /******************************************************************************************************************************************/
    
    soundFile.load(ofToDataPath("sound/paris.wav"));
    soundFile.getLength();
    ofxMaxiSettings::setup(sampleRate, numChannels, 8192);
    ofSoundStreamSetup(1, 0, this, sampleRate, initialBufferSize, 4);
    
    
    /******************************************************** Settings for Dirac starts **************************************************************/
    /*************************************************************************************************************************************************/
    
    numFrames = initialBufferSize;//numFrames is the amount of frames per read operation
    inputNumFrames = mAiffGetNumberOfFrames(infileNameWithPath);
    
    //time and pitch shfiting
    time = 2.0;// stretch time by 200%;
    pitch = pow(2., 0./12.);// // pitch shift (0 semitones)
    
    //create DiracFx objects
    diracFx = DiracFxCreate(kDiracQualityBetter, sampleRate, numChannels);
    if (!diracFx) {
        printf("!! ERROR !!\n\n\tCould not create DiracFx instance\n");
        return ;
    }
    
    /* Initialize the output file */
    mAiffInitFile(outfileNameWithPath, sampleRate /* sample rate */, 16 /* bits */, numChannels);
    
    /* Print version info to stdout */
    printf("Running DIRAC version %s\nStarting processing\n", DiracVersion());
    
    /* Allocate buffer for output */
    audioInBuffer = mAiffAllocateAudioBuffer(numChannels, numFrames);
    audioOutBuffer = mAiffAllocateAudioBuffer(numChannels,
                                                DiracFxMaxOutputBufferFramesRequired(time, pitch, numFrames));
    
    /* ***************** HANDLE LATENCY ******************* */
    /* Get latency estimate */
    latencyFrames = DiracFxLatencyFrames(sampleRate); //latency maybe the addtional frames effected by the speed change.
    
    /* Establish a separate buffer to account for latency. */
    /* We could do this with our processing buffers but we're lazy. */
    float **latencyBufferIn = mAiffAllocateAudioBuffer(numChannels, latencyFrames);
    float **latencyBufferOut = mAiffAllocateAudioBuffer(numChannels,DiracFxMaxOutputBufferFramesRequired(time, pitch, latencyFrames));
    
    /* Read the first chunk from the file */
    mAiffReadData(infileNameWithPath, latencyBufferIn, 0, latencyFrames, numChannels);
    
    /* The first block is processed manually to account for the latency */
    DiracFxProcessFloat(time, pitch, latencyBufferIn,latencyBufferOut, latencyFrames, diracFx);
    
    /* The first block is processed manually to account for the latency */
    /* but increase our read position */
    inputFramesProcessed += latencyFrames;
    
    /******************************************************** Settings for Dirac Ends **************************************************************/
    /***********************************************************************************************************************************************/
    
    
//    /* ***************** MAIN PROCESSING LOOP STARTS HERE ******************* */
//    for(;;) {
//        /* read chunk at position inputFramesProcessed */
//        mAiffReadData(infileNameWithPath, audioInBuffer, inputFramesProcessed, numFrames,numChannels);
//        /* Call the process function with current time and pitch settings */
//        /* Returns: the number of frames in audioOut */
//        long ret = DiracFxProcessFloat(time, pitch, audioInBuffer, audioOutBuffer,numFrames, diracFx);
//        
//        /* Write data to the output file */
//        mAiffWriteData(outfileNameWithPath, audioOutBuffer, ret, numChannels);
//        /* Increase our input position */
//        inputFramesProcessed += numFrames;
//        /* As soon as we've read enough frames we exit the main loop */
//        if (inputFramesProcessed >= inputNumFrames + latencyFrames)
//            break;
//    }
//    /* ***************** END MAIN PROCESSING LOOP ******************* */
//    /* ***************** CLEAN UP ******************* */
//    /* Free processing buffers */
//    mAiffDeallocateAudioBuffer(audioInBuffer, numChannels);
//    mAiffDeallocateAudioBuffer(audioOutBuffer, numChannels);
//    mAiffDeallocateAudioBuffer(latencyBufferIn, numChannels);
//    mAiffDeallocateAudioBuffer(latencyBufferOut, numChannels);
//    /* Destroy DiracFx instance */
//    DiracFxDestroy( diracFx );
//    /* We're done! */
//    printf("\nDone!\n");
//    /* Open audio file via system call on the Mac */
//    system("open out.aiff");
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
}

void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    for (int i=0 ;i < bufferSize ;i++) {
        sample = soundFile.play(2.0);
        myMix.stereo(sample, outputs, 0.5);
        output[i*nChannels    ] = outputs[0]; /* You may end up with lots of outputs. add them here */
        output[i*nChannels + 1] = outputs[1];
    }
    

    
//    if (inputFramesProcessed < inputNumFrames + latencyFrames) {
//        
//        /* read chunk at position inputFramesProcessed to audioInBuffer*/
//        mAiffReadData(infileNameWithPath, audioInBuffer, inputFramesProcessed, numFrames,numChannels);
//        
//        /* Call the process function with current time and pitch settings */
//        /* Returns: the number of frames in audioOut */
//        long ret = DiracFxProcessFloat(time, pitch, audioInBuffer, audioOutBuffer,numFrames, diracFx);
//        for (int i = 0; i < bufferSize; i++){
//            
//            //float wave = timeStretcher->play(speed, grainLength, 5, 0);
//            //play result
//            myMix.stereo(wave, outputs, 0.5);
//            
//            output[i*nChannels    ] = outputs[0]; /* You may end up with lots of outputs. add them here */
//            output[i*nChannels + 1] = outputs[1];
//        }
//    }
//    
//    
//    
//
//    
//    
//    
//    /* ***************** MAIN PROCESSING LOOP STARTS HERE ******************* */
//    for(;;) {
//
//        
//        /* Write data to the output file */
//        mAiffWriteData(outfileNameWithPath, audioOutBuffer, ret, numChannels);
//        
//        /* Increase our input position */
//        inputFramesProcessed += numFrames;
//        
//        /* As soon as we've read enough frames we exit the main loop */
//        if (inputFramesProcessed >= inputNumFrames + latencyFrames)
//            break;
//    }
}

void ofApp::audioIn(float *input, int bufferSize, int nChannels) {
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
