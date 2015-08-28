
#include "PlayShared.h"

PlayShared playshared;

const PlayInitMsg& playconfig()
{
    return playshared.playconfig();
}

//string getJigBack()
//{
//    return sstr("play/bg%d.png", playconfig().cur_level()+1);
//}

string getJigsaw()
{
    return sstr("jigsaw/level%d/jigsaw%02d.png", playconfig().choose_level(), playshared.cur_level+1);
}
