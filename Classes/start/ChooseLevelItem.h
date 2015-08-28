

#ifndef __Jigsaw_ChooseLevelItem_
#define __Jigsaw_ChooseLevelItem_

#include "JigHeader.h"
#include "ChooseItemMsg.pb.h"

class ChooseLevelItem : public cocos2d::ui::Widget
{
public:
	ChooseLevelItem();
	virtual ~ChooseLevelItem() override;

	CREATE_FUNC(ChooseLevelItem);
	
	virtual bool init() override;
    
    void reset(int iMainLevel);

private:
	cocos2d::Node* load_csd();

	void onClickItem(Ref* sender);


private:
    Button* m_btn;
    ImageView* m_img;
    
    int m_iMainLevel;
    bool m_bUnlock;
};

#endif

