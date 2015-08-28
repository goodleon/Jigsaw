

#ifndef __Jigsaw_ConfirmLayer_
#define __Jigsaw_ConfirmLayer_

#include "PlayShared.h"

class ConfirmLayer : public cocos2d::Layer
{
public:
	ConfirmLayer();
	virtual ~ConfirmLayer() override;

    typedef std::function<void(void)> ConfirmListener;
    static ConfirmLayer* create(const string& lan_id, ConfirmListener ok, ConfirmListener cancel);
	
	virtual bool init() override;
    
    void setText(const string& text);
//    void setOkHandler(ConfirmListener ok);
//    void setCancelHandler(ConfirmListener cancel);

private:
	cocos2d::Node* load_csd();

	void onClickCancel(Ref* sender);
	void onClickOk(Ref* sender);


private:
	Text* m_text;
    ConfirmListener m_ok;
    ConfirmListener m_cancel;
};

#endif

