

#ifndef __Jigsaw_PlayDisplay_
#define __Jigsaw_PlayDisplay_

#include "JigHeader.h"

class PlayDisplay : public cocos2d::Layer
{
public:
	PlayDisplay();
	virtual ~PlayDisplay() override;

	CREATE_FUNC(PlayDisplay);
	
	virtual bool init() override;

private:
	cocos2d::Node* load_csd();

    void onTouchPanel(Ref*,Widget::TouchEventType);

private:
	ImageView* m_back;
    ImageView* m_clip_stencil;
};

#endif

