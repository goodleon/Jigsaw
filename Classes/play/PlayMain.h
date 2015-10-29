

#ifndef __Jigsaw_PlayMain_
#define __Jigsaw_PlayMain_

#include "PlayShared.h"

class PlayMain : public cocos2d::Layer
{
public:
	PlayMain();
	virtual ~PlayMain() override;

    static Scene* createScene();

private:
	CREATE_FUNC(PlayMain);
    
	virtual bool init() override;

private:
    cocos2d::Node* load_csd();

    void onClickPrelook(Ref* sender);
    void onClickFinish(Ref* sender);
    void onClickReturnMenu(Ref* sender);

private:
    Layout* m_panel_start;
    Layout* m_game_panel;
};

#endif

