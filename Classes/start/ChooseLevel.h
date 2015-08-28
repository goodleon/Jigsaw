

#ifndef __Jigsaw_ChooseLevel_
#define __Jigsaw_ChooseLevel_

#include "JigHeader.h"
#include "JigScene.h"
#include "ChooseLevelItem.h"

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

	void onClickReturn(Ref* sender);

    void onPageEvent(Ref*, PageView::EventType);
    
    vector<ChooseItemMsg> load_config();

private:
	PageView* m_page;
    Text* m_page_idx;
    
    static const int max_level = 9;
};

#endif

