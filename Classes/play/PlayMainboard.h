

#ifndef __Jigsaw_PlayMainboard_
#define __Jigsaw_PlayMainboard_

#include "PlayShared.h"

class PlayMainboard : public cocos2d::Layer
{
public:
	PlayMainboard();
	virtual ~PlayMainboard() override;

	CREATE_FUNC(PlayMainboard);
	
	virtual bool init() override;

private:
	void load_csd();

	void onClickPause(Ref* sender);
	void onClickFinish(Ref* sender);


private:
	Text* m_time;

};

#endif

