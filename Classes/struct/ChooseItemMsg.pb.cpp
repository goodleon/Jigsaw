
#include "ChooseItemMsg.pb.h"

ChooseItemMsg::ChooseItemMsg()
{
	m_level = 0;
	m_star = 0;
	m_canchoose = false;
}

ChooseItemMsg::~ChooseItemMsg()
{

}


void ChooseItemMsg::set_level(int val)
{
	m_level = val;
}
int ChooseItemMsg::level()
{
	return m_level;
}
int ChooseItemMsg::level() const
{
	return m_level;
}

void ChooseItemMsg::set_star(int val)
{
	m_star = val;
}
int ChooseItemMsg::star()
{
	return m_star;
}
int ChooseItemMsg::star() const
{
	return m_star;
}

void ChooseItemMsg::set_canchoose(bool val)
{
	m_canchoose = val;
}
bool ChooseItemMsg::canchoose()
{
	return m_canchoose;
}
bool ChooseItemMsg::canchoose() const
{
	return m_canchoose;
}
