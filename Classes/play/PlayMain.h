

#ifndef __Jigsaw_PlayMain_
#define __Jigsaw_PlayMain_

#include "PlayShared.h"

class PlayMain : public cocos2d::Layer
{
public:
	PlayMain();
	virtual ~PlayMain() override;

    static Scene* createScene();

private:
	CREATE_FUNC(PlayMain);
    
	virtual bool init() override;

private:
	Node* load_csd();

	void onClickFinish(Ref* sender);
	void onClickPause(Ref* sender);


private:

};

#endif

