

#ifndef __Jigsaw_ChooseLevelItem_
#define __Jigsaw_ChooseLevelItem_

#include "JigHeader.h"

class ChooseLevelItem : public cocos2d::ui::Widget
{
public:
	ChooseLevelItem();
	virtual ~ChooseLevelItem() override;

	CREATE_FUNC(ChooseLevelItem);
	
	virtual bool init() override;

    void reset(int level);
private:
	cocos2d::Node* load_csd();

	void onClickButton(Ref* sender);
	void onClickLock(Ref* sender);


private:
    Button* m_lock;
    int m_mainLevel;
};

#endif

