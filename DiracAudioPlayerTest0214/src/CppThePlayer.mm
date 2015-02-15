//
//  CppThePlayer.cpp
//  DiracAudioPlayerTest0214
//
//  Created by Zhang Xinlei on 2/15/15.
//
//

#include "CppThePlayer.h"
#import "DiracAudioPlayer.h"

CppThePlayer::CppThePlayer()
:ptr(
     [DiracAudioPlayer alloc]
     )
{
    //    NSString *string = [[NSString alloc] initWithFormat:@"/Users/Kular/Downloads/--DIRAC3LE--/Dirac3-Desktop/SMB2MasterDspS.caf"];
    //    NSLog(@"String = %@", string);
    //    NSURL *theUrl = [[NSURL alloc] initWithString:string];
    //    NSError *error;
    //    error = nil;
    //    ptr = [[DiracAudioPlayer alloc] initWithContentsOfURL: theUrl channels:1 error:&error];
    
}

CppThePlayer::~CppThePlayer()
{
    
}

void CppThePlayer::play()
{
    [ptr play];
}
void CppThePlayer::pause()
{
    [ptr pause];
}

void CppThePlayer::setDuration(float duration)
{
    [ptr changeDuration:duration];
}

void CppThePlayer::setPitch(float pitch)
{
    [ptr changePitch:pitch];
}

void CppThePlayer::setParameter(char url[], int nChannels) {
    
    NSString *string = [[NSString alloc] initWithUTF8String:url];
    NSString *filePath = [@"../../../data/" stringByAppendingString:string];
    
    NSLog(@"File Path = %@", filePath);
    NSURL *filePathUrl = [[NSURL alloc] initWithString:filePath];
    
    NSLog(@"URL = %@", filePathUrl);

    NSError *error;
    error = nil;
    
    [ptr initWithContentsOfURL:filePathUrl channels:nChannels error:&error];
    ptr._time = 1;
}

void CppThePlayer::setCurrentTime(float time)
{
    [ptr setCurrentTime:time];
}

void CppThePlayer::setVolume(float volume)
{
    [ptr setVolume:volume];
}

bool CppThePlayer::readToPlay()
{
    return [ptr prepareToPlay];
}

double CppThePlayer::soundTotalDuration()
{
    return [ptr fileDuration];
}

double CppThePlayer::getCurrentTime()
{
    return [ptr currentTime];
}

double CppThePlayer::getCurrentPosition()
{
    return [ptr currentPosition];
}

void CppThePlayer::setCurrentPosition(double position)
{
    [ptr setCurrentPosition:position];
}

float CppThePlayer::getVolume()
{
    return [ptr volume];
}

bool CppThePlayer::playing()
{
    return [ptr playing];
}
