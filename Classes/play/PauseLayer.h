

#ifndef __Jigsaw_PauseLayer_
#define __Jigsaw_PauseLayer_

#include "PlayShared.h"

class PauseLayer : public cocos2d::Layer
{
public:
	PauseLayer();
	virtual ~PauseLayer() override;

	CREATE_FUNC(PauseLayer);
	
	virtual bool init() override;

private:
	void load_csd();

	void onClickContinue(Ref* sender);
	void onClickMainmenu(Ref* sender);


private:

};

#endif

