
#include "PlayInitMsg.h"

PlayInitMsg::PlayInitMsg()
{
	m_main_level = 0;
	m_start_level = 0;
	m_level_count = 0;
	m_rotable = false;
}

PlayInitMsg::~PlayInitMsg()
{

}


void PlayInitMsg::set_main_level(int val)
{
	m_main_level = val;
}
int PlayInitMsg::main_level()
{
	return m_main_level;
}
int PlayInitMsg::main_level() const
{
	return m_main_level;
}

void PlayInitMsg::set_start_level(int val)
{
	m_start_level = val;
}
int PlayInitMsg::start_level()
{
	return m_start_level;
}
int PlayInitMsg::start_level() const
{
	return m_start_level;
}

void PlayInitMsg::set_level_count(int val)
{
	m_level_count = val;
}
int PlayInitMsg::level_count()
{
	return m_level_count;
}
int PlayInitMsg::level_count() const
{
	return m_level_count;
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
