#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    
    //Input file and Output file for audio processing
    char infileNameWithPath[] = "/Users/ZhangXinlei/Programming/openFrameworks/of_v0.8.1_osx_release/apps/Voice Processing/DiracTimeStretchTest0201/test.aif";
    char outfileNameWithPath[] = "/Users/ZhangXinlei/Programming/openFrameworks/of_v0.8.1_osx_release/apps/Voice Processing/DiracTimeStretchTest0201/out.aif";
    
    //sampleRate, numChannels, numFrames
    //Sample Rate is basically 44100;
    sampleRate = mAiffGetSampleRate(infileNameWithPath);
    if (sampleRate <= 0.f) {
        printf("Error opening input file\n");
        return ;
    }
    else {
        printf("Sample Rate is %.2f\n", sampleRate);
    }
    
    //numFrames is the amount of frames per read operation
    initialBufferSize = 8192;
    numFrames = initialBufferSize;
    
    //numChannels = mAiffGetNumberOfChannels(infileName);
    
    numChannels = 1;// Dirac 3LE Supports only 1 channel currently
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
    /* Keep track of how many frames we've already processed */
    unsigned long inputFramesProcessed = 0;
    
    /* Allocate buffer for output */
    audioInBuffer = mAiffAllocateAudioBuffer(numChannels, numFrames);
    audioOutBuffer = mAiffAllocateAudioBuffer(numChannels,
                                                DiracFxMaxOutputBufferFramesRequired(time, pitch, numFrames));
    
    /* ***************** HANDLE LATENCY ******************* */
    /* Get latency estimate */
    long latencyFrames = DiracFxLatencyFrames(sampleRate);
    
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
    
    /* ***************** MAIN PROCESSING LOOP STARTS HERE ******************* */
    for(;;) {
        /* read chunk at position inputFramesProcessed */
        mAiffReadData(infileNameWithPath, audioInBuffer, inputFramesProcessed, numFrames,numChannels);
        /* Call the process function with current time and pitch settings */
        /* Returns: the number of frames in audioOut */
        long ret = DiracFxProcessFloat(time, pitch, audioInBuffer, audioOutBuffer,numFrames, diracFx);
        
        /* Write data to the output file */
        mAiffWriteData(outfileNameWithPath, audioOutBuffer, ret, numChannels);
        /* Increase our input position */
        inputFramesProcessed += numFrames;
        /* As soon as we've read enough frames we exit the main loop */
        if (inputFramesProcessed >= inputNumFrames + latencyFrames)
            break;
    }
//    /* ***************** END MAIN PROCESSING LOOP ******************* */
//    /* ***************** CLEAN UP ******************* */
//    /* Free processing buffers */
//    mAiffDeallocateAudioBuffer(audioInBuffer, numChannels);
//    mAiffDeallocateAudioBuffer(audioOutBuffer, numChannels);
//    mAiffDeallocateAudioBuffer(latencyBufferIn, numChannels);
//    mAiffDeallocateAudioBuffer(latencyBufferOut, numChannels);
//    /* Destroy DiracFx instance */
//    DiracFxDestroy( diracFx );
    /* We're done! */
    printf("\nDone!\n");
    /* Open audio file via system call on the Mac */
    system("open out.aiff");
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
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
