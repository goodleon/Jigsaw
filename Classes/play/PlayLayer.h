

#ifndef __Jigsaw__PlayLayer__
#define __Jigsaw__PlayLayer__

#include "PlayShared.h"
#include "JigTile.h"

class PlayLayer : public cocos2d::Layer
{
public:
	PlayLayer();
	virtual ~PlayLayer();

	CREATE_FUNC(PlayLayer);
	static cocos2d::Scene* createScene();
    
	virtual bool init();

private:
    
private:

};

#endif /* defined(__Jigsaw__PlayLayer__) */

