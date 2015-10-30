

#ifndef __Jigsaw_ThanksLayer_
#define __Jigsaw_ThanksLayer_

#include "JigHeader.h"

class ThanksLayer : public cocos2d::Layer
{
public:
	ThanksLayer();
	virtual ~ThanksLayer() override;

    static JigScene* createScene();
private:
	CREATE_FUNC(ThanksLayer);
	
	virtual bool init() override;

private:
	cocos2d::Node* load_csd();

	void onClickReturn(Ref* sender);


private:

};

#endif

