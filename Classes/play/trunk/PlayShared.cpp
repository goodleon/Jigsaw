
#include "PlayShared.h"

PlayShared playshared;

string PlayShared::getJigsaw()
{
    return sstr("jigsaw/level%d/jigsaw%02d.png", 0, cur_level);
}

PlayShared::PlayShared()
{
    resetAll();
}

void PlayShared::resetNewlevel()
{
    esptime = -1;
    rows = cols = -1;
}

void PlayShared::resetAll()
{
    play_scene = nullptr;
    jig_panel = nullptr;
    cur_level = -1;
    resetNewlevel();
}

const PlayInitMsg& PlayShared::config() const
{
    return m_config;
}
