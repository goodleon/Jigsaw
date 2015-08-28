

#include "TimeHpBar.h"
#include "PlayManager.h"
#include "LanguageMgr.h"

TimeHpBar::TimeHpBar()
{

}

TimeHpBar::~TimeHpBar()
{

}

bool TimeHpBar::init()
{
	Return_False_If(!Layer::init());

	Node* root = load_csd();
	addChild(root);

	return true;
}

void TimeHpBar::onStateChanged(GameState gs)
{
    if (gs == gs_prepare)
    {
        m_timebar->setPercent(100.0f);
    }
    else if (gs == gs_playing)
    {
        start();
    }
    else if (gs == gs_pause)
    {
        pause();
    }
    else
    {
        stop();
    }
}

Node* TimeHpBar::load_csd()
{
	Node* root = CSLoader::createNode("timebar.csb");

	m_timebar = static_cast<LoadingBar*>(root->getChildByName("timebar"));
    m_text = static_cast<Text*>(root->getChildByName("text"));

    return root;
}

void TimeHpBar::onSecondTick(float diff)
{
    ++playshared.esptime;
    if (playshared.esptime <= playconfig().max_time())
    {
        float div = playshared.esptime*1.0f / playconfig().max_time();
        m_timebar->setPercent( (1.0f-div)*100 );
        m_text->setString( sstr("%f", (1.0f-div)*100) );
    }
    else
    {
        stop();
        GameStateMgr::inst().change(gs_dead);
    }
}

void TimeHpBar::start()
{
    this->schedule(SEL_SCHEDULE(&TimeHpBar::onSecondTick), 1.0f);
}

void TimeHpBar::pause()
{
    this->unschedule( SEL_SCHEDULE(&TimeHpBar::onSecondTick) );
//    m_text->setString( "pause" );
}

void TimeHpBar::stop()
{
    this->unschedule( SEL_SCHEDULE(&TimeHpBar::onSecondTick) );
//    m_text->setString( "stop" );
}

