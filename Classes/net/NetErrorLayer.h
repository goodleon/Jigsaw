

#ifndef __Jigsaw_NetErrorLayer_
#define __Jigsaw_NetErrorLayer_

#include "JigHeader.h"
#include "JigNotify.h"

class NetErrorLayer : public cocos2d::Layer, public JigNotify
{
public:
	NetErrorLayer();
	virtual ~NetErrorLayer() override;

	CREATE_FUNC(NetErrorLayer);
	
	virtual bool init() override;

    void setErrorMessage(const string& msg);

    virtual void onMessage(int notify_id, const net_data_t& root);
private:
	cocos2d::Node* load_csd();

	void onClickRetry(Ref* sender);
	void onClickExit(Ref* sender);


private:
	Text* m_errorMsg;
    TextField* m_server_addr;
};

#endif

