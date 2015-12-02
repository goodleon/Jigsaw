//
//  JigAudio.cpp
//  Jigsaw
//
//  Created by zhangdw on 15-11-30.
//
//

#include "JigAudio.h"

void playEffect(const char* audio_file)
{
    SimpleAudioEngine::getInstance()->playEffect(audio_file);
}