//
//  Sample.cpp
//  samplePlaybackTest
//
//  Created by Zhang Xinlei on 1/9/15.
//
//

#include "Sample.h"
#include "ofMain.h"

#define MS_per_S 1000


Sample::~Sample()
{
    //delete myPath;
    delete myData;
    myChunkSize = NULL;
    mySubChunk1Size = NULL;
    myFormat = NULL;
    myChannels = NULL;
    mySampleRate = NULL;
    myByteRate = NULL;
    myBlockAlign = NULL;
    myBitsPerSample = NULL;
    myDataSize = NULL;
}

// empty constructor
Sample::Sample()
{
    position = 0;
    speed = 1.0;
    soundStatus = NONE;
}

// constructor takes a wav path
Sample::Sample(string tmpPath)
{
    position = 0;
    speed = 1.0;
    soundStatus = NONE;
    
    myPath = tmpPath;
    read();
}

void Sample::setPath(string tmpPath)
{
    myPath = tmpPath;
    
}

void Sample::setLooping(bool loop)
{
    if(loop) {
        soundStatus |= LOOPING;
    }
    else {
        soundStatus &= ~LOOPING;
    }
}

bool Sample::getIsLooping()
{
    if(soundStatus & LOOPING) return true;
    else return false;
}

bool Sample::getIsLoaded()
{
    if(soundStatus & LOADED) return true;
    else return false;
}

bool Sample::getIsPlaying()
{
    if(soundStatus & PLAYING) return true;
    else return false;
}

bool Sample::getIsPaused()
{
    if(soundStatus & PAUSED) return true;
    else return false;
}

bool Sample::load(string tmpPath) {
    myPath = tmpPath;
    bool result = read();//read the wav file from the given path
    return result;
}

void Sample::generateWaveForm(vector<MiniMaxima> * _waveForm)
{
    
    _waveForm->clear();
    
    bool loopState = getIsLooping();
    setLooping(false);
    bool playState = getIsPlaying();
    double tmpSpeed = getSpeed();
    setSpeed(1.0f);
    play();
    // waveform display method based on this discussion http://answers.google.com/answers/threadview/id/66003.html
    
    double sampleL, sampleR;
    
    while ((long)position < getLength()) {
        
        MiniMaxima mm;
        mm.minL = mm.minR = mm.maxL = mm.maxR = 0;
        
        for (int i = 0; i < 256; i++){
            
            if(myChannels == 1) {//单声道
                sampleL = update();
                sampleR = sampleL;
            }
            else {//双声道
                sampleL = update()*0.5;// Sampling data is arranged in order L,R,L,R,L,R... So a pair of <L,R> stands for one sample ?
                sampleR = update()*0.5;
            }
            
            mm.minL = MIN(mm.minL, sampleL);
            mm.minR = MIN(mm.minR, sampleR);
            mm.maxL = MAX(mm.maxL, sampleL);
            mm.maxR = MAX(mm.maxR, sampleR);
            
        }
        
        _waveForm->push_back(mm);
        
    }
    
    position = 0;
    setLooping(loopState);
    setSpeed(tmpSpeed);
    if(playState)
        play();
}

vector<std::pair<float, float> > Sample::getPausePostionPairs()
{
    PausePositionPairs.clear();
    
    bool loopState = getIsLooping();
    setLooping(false);
    bool playState = getIsPlaying();
    double tmpSpeed = getSpeed();
    setSpeed(1.0f);
    play();
    
    double sampleL, sampleR;
    
    pair<float, float> tmpPairs;
    vector<float> mutePositions;
    float minPauseTime = ((getChannels() == 1)? 0.05 : 0.15 )/ (getTotalTime());
    
    while ((long)position < getLength()) {
        if(myChannels == 1) {
            sampleL = update()*MS_per_S;
            sampleR = sampleL;
            
            if (abs(sampleL) < 5) { // 5 or 10
                mutePositions.push_back(getPosition());
                
            } else {
                
                if (mutePositions.size() < minPauseTime * getLength() / getChannels()) {
                    if (!mutePositions.empty())
                        mutePositions.clear();
                    
                } else {
                    cout<<"Pushed!!!"<<endl;
                    tmpPairs.first = mutePositions.at(0);
                    tmpPairs.second = mutePositions.at(mutePositions.size() - 1);
                    PausePositionPairs.push_back(tmpPairs);
                    std::cout<<"Pair("<<tmpPairs.first<<", "<<tmpPairs.second<<")"<<endl;
                    mutePositions.clear();
                }
            }
            
        }
        else {
            sampleL = (int)(update()*0.5*MS_per_S);
            sampleR = (int)(update()*0.5*MS_per_S);
            
            //            cout<<"sampleL: "<<sampleL<<" : sampleR: "<<sampleR<<endl;
            
            if (abs(sampleL) < 8 || abs(sampleR) < 8) {
                //                cout<<"Pushing..."<<endl;
                //                cout<<"getPosition: "<<getPosition()<<endl;
                mutePositions.push_back(getPosition());
                //                cout<<"mutePositions.size() = "<<mutePositions.size()<<endl;
            }
            else {
                if (mutePositions.size() < minPauseTime * getLength() / getChannels()) {
                    if (!mutePositions.empty())
                        mutePositions.clear();
                    //                    cout<<"Cleared! size: "<<mutePositions.size()<<endl;
                } else {
                    cout<<"Pushed!!!"<<endl;
                    tmpPairs.first = mutePositions.at(0);
                    tmpPairs.second = mutePositions.at(mutePositions.size() - 1);
                    PausePositionPairs.push_back(tmpPairs);
                    std::cout<<"Pair("<<tmpPairs.first<<", "<<tmpPairs.second<<")"<<endl;
                    mutePositions.clear();
                }
            }
            
        }
    }
    
    position = 0;
    setLooping(loopState);
    setSpeed(tmpSpeed);
    if(playState)
        play();
    
    return PausePositionPairs;
}

int Sample::getTotalTime()
{
    return getLength()/getChannels()/getSampleRate();
}

//Get this !
void Sample::drawWaveForm(int _x, int _y, int _w, int _h, vector<MiniMaxima> * _waveForm)
{
    // pixel number in X-axis for each sample to display in a space whose width is [0, _w -1];
    float waveFormZoomX = (float)_waveForm->size()/(float)_w;
    
    glPushMatrix();
    
    // WaveForm start drawing position (_x, _y)
    glTranslated(_x, _y, 0);
    
    //    std::vector<long> mutePositions;
    
    // draw each wave unit based on elements in the vector
    for (unsigned int i = 1; i < _waveForm->size(); i++){
        if(myChannels == 1) {
            ofSetColor(0, 0, 255);
            ofLine((i-1)/waveFormZoomX, _h + (int)(_waveForm->at(i-1).minR*_h), i/waveFormZoomX, _h +  (int)(_waveForm->at(i).maxR*_h));
            
            
            ofSetColor(0, 255, 0);
            ofLine(i/waveFormZoomX, _h + (int)(_waveForm->at(i).maxR*_h), i/waveFormZoomX, _h + (int)(_waveForm->at(i).minR*_h));
            
        } else {
            ofSetColor(255, 0, 0);// 左声道
            ofLine((i-1)/waveFormZoomX, _waveForm->at(i).minR*(float)_h, i/waveFormZoomX, _waveForm->at(i).maxR*(float)_h);
            
            if ((int)(_waveForm->at(i).maxL*_h) - (int)(_waveForm->at(i).minL*_h) < 3 )
                ofSetHexColor(0x2a2a32);
            else ofSetHexColor(0xff0000);//red
            
            
            ofLine((i-1)/waveFormZoomX, (int)(_waveForm->at(i-1).minL*_h), i/waveFormZoomX, (int)(_waveForm->at(i).maxL*_h));
            
            
            if ((int)(_waveForm->at(i).minL*_h) - (int)(_waveForm->at(i).maxL*_h) > -3 )
                ofSetHexColor(0x00622a0);
            else ofSetHexColor(0xff0000);//red
            
            ofLine(i/waveFormZoomX, (int)(_waveForm->at(i).maxL*_h), i/waveFormZoomX, (int)(_waveForm->at(i).minL*_h));
            
            ofSetColor(0, 0, 255);// 右声道
            ofLine((i-1)/waveFormZoomX, _h + (int)(_waveForm->at(i-1).minR*_h), i/waveFormZoomX, _h +  (int)(_waveForm->at(i).maxR*_h));
            ofLine(i/waveFormZoomX, _h + (int)(_waveForm->at(i).maxR*_h), i/waveFormZoomX, _h + (int) (_waveForm->at(i).minR*_h));
        }
    }
    
    ofSetColor(0, 255, 0);
    
    float waveFormDisplayScale = getLength()/_w;
    
    if(myChannels == 1) {
        ofLine(position/waveFormDisplayScale, -(float)_h*0.0, position/waveFormDisplayScale, (float)_h*2.0);
    }
    else
    {
        ofLine(position/waveFormDisplayScale, -(float)_h*0.5, position/waveFormDisplayScale, (float)_h*1.5);
    }
    
    glPopMatrix();
}

void Sample::stop()
{
    position = 0;
    soundStatus &= ~PAUSED;
    soundStatus &= ~PLAYING;
}

void Sample::play()
{
    if(speed > 0)
        position = 0;
    else
        position = getLength();
    soundStatus |= PLAYING;
}

void Sample::setPaused(bool bPaused)
{
    if(bPaused) {
        soundStatus |= PAUSED;
    }
    else {
        soundStatus &= ~PAUSED;
    }
}

void Sample::setSpeed(double spd)
{
    speed = spd;
}

double Sample::getSpeed()
{
    return speed;
}

int Sample::getSampleRate()
{
    return mySampleRate;
}

double Sample::update()
{
    if(!(soundStatus & PLAYING)) return 0;
    if(soundStatus & PAUSED) return 0;
    if(!getIsLoaded()) return 0;
    
    long length=getLength();
    double remainder;
    short* buffer = (short *)myData;
    position=(position+speed);
    remainder = position - (long) position;
    
    // check if reached EOF.
    // If it is and it's under looping mode, then reset position, else stop playing it.
    if ((long) position>length) {
        if(getIsLooping()) {
            position=0;
        }
        else {
            soundStatus &= ~PLAYING;
            return 0;
        }
    }
    
    //check if position less than zero (reverse)
    if ((long) position < 0) {
        if(getIsLooping()) {
            position = length;
        }
        else {
            soundStatus &= ~PLAYING;
            return 0;
        }
    }
    
    output = (double) ((1.0-remainder) * buffer[1+ (long) position] + remainder * buffer[2+(long) position])/32767.0;//linear interpolation
    
    return(output);
}

long Sample::getLength()
{
    long length;
    length=myDataSize*0.5;
    return(length);
}
double Sample::getPosition()
{
    double pos = position/getLength();
    pos = ofClamp(pos,0.0,1.0);//restrict the pos to between [0.0, 1.0]
    return pos;
}
void Sample::setPosition(double _position)
{
    double pct = ofClamp(_position,0.0,1.0);
    position = pct * getLength();
}
// return a printable summary of the wav file
char* Sample::getSummary()
{
    char *summary = new char[250];
    sprintf(summary, " Format: %d\n Channels: %d\n SampleRate: %d\n ByteRate: %d\n BlockAlign: %d\n BitsPerSample: %d\n DataSize: %d\n", myFormat, myChannels, mySampleRate, myByteRate, myBlockAlign, myBitsPerSample, myDataSize);
    std::cout << myDataSize;
    return summary;
}

int Sample::getChannels()
{
    return myChannels;
}


/*
 Wav file format may refer to this link
 http://www.topherlee.com/software/pcm-tut-wavformat.html
 */

// write out the wav file
bool Sample::save()
{
    ofToDataPath(myPath);
    fstream myFile (myPath.c_str(), ios::out | ios::binary);
    
    // write the wav file per the wav file format
    myFile.seekp (0, ios::beg);
    myFile.write ("RIFF", 4);
    myFile.write ((char*) &myChunkSize, 4);
    myFile.write ("WAVE", 4);
    myFile.write ("fmt ", 4);
    myFile.write ((char*) &mySubChunk1Size, 4);
    myFile.write ((char*) &myFormat, 2);
    myFile.write ((char*) &myChannels, 2);
    myFile.write ((char*) &mySampleRate, 4);
    myFile.write ((char*) &myByteRate, 4);
    myFile.write ((char*) &myBlockAlign, 2);
    myFile.write ((char*) &myBitsPerSample, 2);
    myFile.write ("data", 4);
    myFile.write ((char*) &myDataSize, 4);
    myFile.write (myData, myDataSize);
    
    return true;
}

// read a wav file into this class
bool Sample::read()
{
    //get the absolute path of the path user specified.
    myPath = ofToDataPath(myPath,true).c_str();
    //read a binary file
    ifstream inFile( myPath.c_str(), ios::in | ios::binary);
    
    
    ofLog(OF_LOG_NOTICE, "Reading file %s",myPath.c_str());
    
    if(!inFile.is_open())
    {
        ofLog(OF_LOG_ERROR,"Error opening file. File not loaded.");
        return false;
    }
    
    
    //Following codes are based on the WAVE file format
    
    //ChunkID
    char id[4];
    inFile.read((char*) &id, 4);
    if(strncmp(id,"RIFF",4) != 0)
    {
        ofLog(OF_LOG_ERROR,"Error reading sample file. File is not a RIFF (.wav) file");
        return false;
    }
    
    //Seek the position for each property and read it. Following percedure are similar
    inFile.seekg(4, ios::beg);
    inFile.read( (char*) &myChunkSize, 4 ); // read the ChunkSize
    
    inFile.seekg(16, ios::beg);
    inFile.read( (char*) &mySubChunk1Size, 4 ); // read the SubChunk1Size
    
    //inFile.seekg(20, ios::beg);
    inFile.read( (char*) &myFormat, sizeof(short) ); // read the file format.  This should be 1 for PCM
    if(myFormat != 1) {
        ofLog(OF_LOG_ERROR, "File format should be PCM, sample file failed to load.");
        return false;
    }
    
    //inFile.seekg(22, ios::beg);
    inFile.read( (char*) &myChannels, sizeof(short) ); // read the # of channels (1 or 2)
    
    //inFile.seekg(24, ios::beg);
    inFile.read( (char*) &mySampleRate, sizeof(int) ); // read the SampleRate
    
    //inFile.seekg(28, ios::beg);
    inFile.read( (char*) &myByteRate, sizeof(int) ); // read the byterate
    
    //inFile.seekg(32, ios::beg);
    inFile.read( (char*) &myBlockAlign, sizeof(short) ); // read the blockalign
    
    //inFile.seekg(34, ios::beg);
    inFile.read( (char*) &myBitsPerSample, sizeof(short) ); // read the bitsperSample, 2 byte
    
    inFile.seekg(40, ios::beg);
    inFile.read( (char*) &myDataSize, sizeof(int) ); // read the size of the data, 4 btye
    //cout << myDataSize << endl;
    
    // read the data chunk
    myData = new char[myDataSize];
    inFile.seekg(44, ios::beg);
    inFile.read(myData, myDataSize);
    
    //print out the read data
    printf("The dataSize is %d\n", myDataSize);
//    for (int i = 0; i < myDataSize; i++)
//        printf("The sample # %d is %d\n", i, (int)myData[i]);
    
    inFile.close(); // close the input file
    
    soundStatus |= LOADED;
    
    return true; // this should probably be something more descriptive
}
