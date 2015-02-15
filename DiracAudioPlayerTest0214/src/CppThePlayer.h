////
////  CppThePlayer.h
////  DiracAudioPlayerTest0214
////
////  Created by Zhang Xinlei on 2/15/15.
////
////
//
//#ifndef __DiracAudioPlayerTest0214__CppThePlayer__
//#define __DiracAudioPlayerTest0214__CppThePlayer__
//
//#include <stdio.h>
//
//#endif /* defined(__DiracAudioPlayerTest0214__CppThePlayer__) */


//
//  CppThePlayer.h
//  objcInCpp
//
//  Created by Kular on 7/29/13.
//
//

#ifndef __objcInCpp__CppThePlayer__
#define __objcInCpp__CppThePlayer__

#ifdef __OBJC__
@class DiracAudioPlayer;
typedef DiracAudioPlayer *PlayerPtr;
#else
typedef void *PlayerPtr;
#endif

#include <iostream>

class CppThePlayer{
    
public:
    CppThePlayer();
    virtual ~CppThePlayer();
    
    void setParameter(char url[], int nChannels);
    
    bool readToPlay();
    
    double soundTotalDuration();
    double getCurrentTime();
    float  getVolume();
    
    
    void play();
    void pause();
    
    void setDuration(float duration);
    void setPitch(float pitch);
    
    void setCurrentTime(float time);
    void setVolume(float volume);
    
    double getCurrentPosition();
    void setCurrentPosition(double position);
    
    bool playing();
    
private:
    PlayerPtr ptr;
    
};


#endif /* defined(__objcInCpp__CppThePlayer__) */
