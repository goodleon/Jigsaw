

#ifndef __Jigsaw_LevelPassView_
#define __Jigsaw_LevelPassView_

#include "JigHeader.h"

class LevelPassView : public cocos2d::Layer
{
public:
	LevelPassView();
	virtual ~LevelPassView() override;

	CREATE_FUNC(LevelPassView);
	
	virtual bool init() override;

    void reset(int iMainLevel);

private:
	cocos2d::Node* load_csd();



private:
	ListView* m_scroll;

};

#endif

