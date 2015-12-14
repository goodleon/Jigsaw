

#ifndef __Jigsaw_StartLayer_
#define __Jigsaw_StartLayer_

#include "JigHeader.h"
#include "JigNotify.h"
#include "NetErrorLayer.h"

class StartLayer : public cocos2d::Layer, public NotifyListener
{
public:
	StartLayer();
	virtual ~StartLayer() override;

    static JigScene* createScene();

    virtual void onMessage(int notify_id, const net_data_t& root);
private:
	CREATE_FUNC(StartLayer);
	
	virtual bool init() override;

private:
	cocos2d::Node* load_csd();

	void onClickStart(Ref* sender);
	void onClickThanks(Ref* sender);


private:
    Text* m_version;
    Text* m_userid;

//    bool m_login;
};

#endif

