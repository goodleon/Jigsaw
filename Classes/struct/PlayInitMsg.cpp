
#include "PlayInitMsg.h"

PlayInitMsg::PlayInitMsg()
{
	m_max_level = 0;
	m_rotable = false;
}

PlayInitMsg::~PlayInitMsg()
{

}


void PlayInitMsg::set_max_level(int val)
{
	m_max_level = val;
}
int PlayInitMsg::max_level()
{
	return m_max_level;
}
int PlayInitMsg::max_level() const
{
	return m_max_level;
}

void PlayInitMsg::set_rotable(bool val)
{
	m_rotable = val;
}
bool PlayInitMsg::rotable()
{
	return m_rotable;
}
bool PlayInitMsg::rotable() const
{
	return m_rotable;
}
