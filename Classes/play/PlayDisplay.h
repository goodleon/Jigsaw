

#ifndef __Jigsaw_PlayDisplay_
#define __Jigsaw_PlayDisplay_

#include "JigHeader.h"
#include "JigLayer.h"

class PlayDisplay : public JigLayer
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

