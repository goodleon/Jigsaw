

#ifndef __Jigsaw_WinLayer_
#define __Jigsaw_WinLayer_

#include "JigHeader.h"

class WinLayer : public cocos2d::Layer
{
public:
	WinLayer();
	virtual ~WinLayer() override;

	CREATE_FUNC(WinLayer);
	
	virtual bool init() override;

private:
	cocos2d::Node* load_csd();

	void onClickRestart(Ref* sender);
	void onClickMainMenu(Ref* sender);
	void onClickNext(Ref* sender);


private:
    vector<ImageView*> m_stars;
};

#endif

