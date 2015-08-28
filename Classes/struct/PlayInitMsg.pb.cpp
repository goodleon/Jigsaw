
#include "PlayInitMsg.pb.h"

PlayInitMsg::PlayInitMsg()
{
	m_choose_level = 0;
	m_start_jiglevel = 0;
	m_max_level = 0;
	m_rotable = false;
	m_shadow = false;
	m_max_time = 0;
}

PlayInitMsg::~PlayInitMsg()
{

}


void PlayInitMsg::set_choose_level(int val)
{
	m_choose_level = val;
}
int PlayInitMsg::choose_level()
{
	return m_choose_level;
}
int PlayInitMsg::choose_level() const
{
	return m_choose_level;
}

void PlayInitMsg::set_start_jiglevel(int val)
{
	m_start_jiglevel = val;
}
int PlayInitMsg::start_jiglevel()
{
	return m_start_jiglevel;
}
int PlayInitMsg::start_jiglevel() const
{
	return m_start_jiglevel;
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

void PlayInitMsg::set_shadow(bool val)
{
	m_shadow = val;
}
bool PlayInitMsg::shadow()
{
	return m_shadow;
}
bool PlayInitMsg::shadow() const
{
	return m_shadow;
}

void PlayInitMsg::set_max_time(int val)
{
	m_max_time = val;
}
int PlayInitMsg::max_time()
{
	return m_max_time;
}
int PlayInitMsg::max_time() const
{
	return m_max_time;
}
