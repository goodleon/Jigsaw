

#ifndef __Jigsaw_ChooseLevel_
#define __Jigsaw_ChooseLevel_

#include "JigHeader.h"

class ChooseLevel : public cocos2d::Layer
{
public:
	ChooseLevel();
	virtual ~ChooseLevel() override;

    static JigScene* createScene();

private:
	CREATE_FUNC(ChooseLevel);
	
	virtual bool init() override;

private:
	cocos2d::Node* load_csd();

	void onClickClose(Ref* sender);
	void onClickRight(Ref* sender);
	void onClickLeft(Ref* sender);


private:
	PageView* m_scroll;

    static const int m_max_level = 9;
};

#endif

