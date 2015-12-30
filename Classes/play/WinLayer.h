

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

    void onClickReturn(Ref* sender);
    void onClickNext(Ref* sender);


private:
    ImageView* m_Image_1;
    Text* m_cur_score;
    ImageView* m_Image_2;
    Text* m_Text_1_0_0;
    Text* m_highest;
    Text* m_Text_1;

};

#endif

