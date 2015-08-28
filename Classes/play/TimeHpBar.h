

#ifndef __Jigsaw_TimeHpBar_
#define __Jigsaw_TimeHpBar_

#include "PlayShared.h"
#include "GameState.h"

class TimeHpBar : public cocos2d::Layer, public GameStateListener
{
public:
	TimeHpBar();
	virtual ~TimeHpBar() override;

	CREATE_FUNC(TimeHpBar);
	
	virtual bool init() override;
    
    virtual void onStateChanged(GameState gs) override;

private:
	cocos2d::Node* load_csd();

    void onSecondTick(float diff);
    
    void start();
    void pause();
    void stop();

private:
	LoadingBar* m_timebar;
	Text* m_text;
};

#endif

