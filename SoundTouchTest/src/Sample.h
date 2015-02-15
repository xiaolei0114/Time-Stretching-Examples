//
//  Sample.h
//  samplePlaybackTest
//
//  Created by Zhang Xinlei on 1/9/15.
//
//

#ifndef __samplePlaybackTest__Sample__
#define __samplePlaybackTest__Sample__

#include <iostream>

#endif /* defined(__SmartVoice_Jul4__Sample__) */

#ifndef SAMPLE_H
#define SAMPLE_H

#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>

//L/R channel's min and max volume ?
typedef struct {
    double minL;
    double maxL;
    double minR;
    double maxR;
} MiniMaxima;

using namespace std;

class Sample {
    
public:
    
    // constructors/desctructor
    ~Sample();
    Sample();
    Sample(string tmpPath);
    
    // methods
    string	getPath() { return myPath;}
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
    int		getChannels();
    int		getSampleRate();
    int     getTotalTime();
    long	getLength();
    
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
    short 	myBitsPerSample;//wav format data: BitsPerSample
    int		myDataSize;//wav format data: Subchunk2Size
    
    
    
    
    double	position;//current playing postion
    double	speed;
    double	output;
    bool    isLooping;
    unsigned char soundStatus;
    //int     playbackSamplerRate;
    vector<std::pair<float, float> > PausePositionPairs;
};


#endif // SAMPLER_H
