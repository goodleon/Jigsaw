

#ifndef __Jigsaw_StartLayer_
#define __Jigsaw_StartLayer_

#include "JigHeader.h"

class StartLayer : public cocos2d::Layer
{
public:
	StartLayer();
	virtual ~StartLayer() override;

    static JigScene* createScene();
private:
	CREATE_FUNC(StartLayer);
	
	virtual bool init() override;

private:
	cocos2d::Node* load_csd();

	void onClickStart(Ref* sender);
	void onClickThanks(Ref* sender);


private:

};

#endif

