//
//  WavFile.h
//  SoundTouchTest
//
//  Created by Zhang Xinlei on 2/7/15.
//
//

#ifndef __SoundTouchTest__WavFile__
#define __SoundTouchTest__WavFile__

#include <iostream>

#endif /* defined(__SoundTouchTest__WavFile__) */
#ifndef WAVFILE_H
#define WAVFILE_H

#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//L/R channel's min and max volume ?
typedef struct {
    double minL;
    double maxL;
    double minR;
    double maxR;
} MiniMaxima;

class WavFile {
    
public:
    
    // constructors/desctructor
    ~WavFile();
    WavFile();
    WavFile(string tmpPath);
    
    // methods
    string	getPath();
    bool    getIsLooping();
    bool    getIsLoaded();
    bool    getIsPlaying();
    bool    getIsPaused();
    double	getPosition();
    double  getSpeed();
    
    void	setPath(string newPath);
    void	setLooping(bool loop);
    void	setPosition(double _position);
    void    setPaused(bool bPaused);
    void    setSpeed(double speed);
    
    bool	load(string tmpPath);
    bool	read();
    void	play();
    void    stop();
    double  update();
    
    bool	save();
    char    *getSummary();
    int		getNumChannels();
    int		getSampleRate();
    int     getBitsPerSample();
    int     getTotalTime();
    long	getLength();
    int     getDataSize();
    
    void	generateWaveForm(vector<MiniMaxima> * _WaveForm);
    void	drawWaveForm(int _x, int _y, int _w, int _h, vector<MiniMaxima> * _WaveForm);
    
    vector<std::pair<float, float> > getPausePostionPairs();
    
    // public variables
    char* 	myData;
    
private:
    
    enum SoundFlags { NONE = 0, LOADED = 1, PLAYING = 2, PAUSED = 4, LOOPING = 8 };
    //Good = Open | Edit | Save | Close,
    //Bad = Corrupt | Busy
    
    /* Variables for saving WAVE Format File */
    string  myPath;
    int 	myChunkSize;//wav format data: ChunkSize
    int		mySubChunk1Size;//wav format data: Subchunk1ID
    short 	myFormat;//wav format data: Audio Format
    short 	myChannels;//wav format data: NumChannels
    int   	mySampleRate;//wav format data: SampleRate
    int   	myByteRate;//wav format data: ByteRate
    short 	myBlockAlign;//wav format data: BlockAlign
    short 	myBitsPerSample;//wav format data: BitsPerSample. BitsPerSample/ 8 = BytePerSample. Number of Samples in data is: DataSize/BytePerSample.
    int		myDataSize;//wav format data: Subchunk2Size. Number of Bytes in total. 
    
    
    
    
    double	position;//current playing postion
    double	speed;
    double	output;
    bool    isLooping;
    unsigned char soundStatus;
    //int     playbackSamplerRate;
    vector<std::pair<float, float> > PausePositionPairs;
};


#endif // WAVFILE_H
