

#ifndef __Jigsaw_TipsLayer_
#define __Jigsaw_TipsLayer_

#include "JigHeader.h"

class TipsLayer : public cocos2d::Layer
{
public:
	TipsLayer();
	virtual ~TipsLayer() override;

	CREATE_FUNC(TipsLayer);
	
	virtual bool init() override;

    void addContent(cocos2d::Node* content);

private:
	cocos2d::Node* load_csd();

    void onTouchPanel(Ref*,Widget::TouchEventType);

private:
	Layout* m_panel;

};

#endif

