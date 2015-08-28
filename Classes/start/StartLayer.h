

#ifndef __Jigsaw_StartLayer_
#define __Jigsaw_StartLayer_

#include "PlayShared.h"

class StartLayer : public cocos2d::Layer
{
public:
	StartLayer();
	virtual ~StartLayer() override;

    static Scene* createScene();
    
	CREATE_FUNC(StartLayer);
	
	virtual bool init() override;

private:
	void load_csd();

	void onClickStart(Ref* sender);


private:

};

#endif

