
#include "PlayShared.h"

PlayShared playshared;

string PlayShared::getJigsaw()
{
    const string file = sstr("jigsaw%d/pic%02d.gif", config().main_level(), cur_level);
    return FileUtils::getInstance()->fullPathForFilename( file );
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
