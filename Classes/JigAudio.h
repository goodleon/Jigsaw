//
//  JigAudio.h
//  Jigsaw
//
//  Created by zhangdw on 15-11-30.
//
//

#ifndef __Jigsaw__JigAudio__
#define __Jigsaw__JigAudio__

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

static const char* audio_background = "sound/play_back.mp3";
static const char* audio_btn = "sound/click_button.wav";
static const char* audio_btn_error = "sound/click_error.wav";
static const char* audio_toast = "sound/toast_tip.wav";
static const char* audio_level_win = "sound/level_win.wav";
static const char* audio_drop_end = "sound/drop_end.wav";
static const char* audio_unknown = "sound/confused.wav";

void playEffect(const char* audio_file);

#endif /* defined(__Jigsaw__JigAudio__) */
