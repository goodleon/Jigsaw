

#ifndef __Jigsaw_WinLayer_
#define __Jigsaw_WinLayer_

#include "JigHeader.h"
#include "JigNotify.h"

class WinLayer : public cocos2d::Layer, public NotifyListener
{
public:
	WinLayer();
	virtual ~WinLayer() override;

	CREATE_FUNC(WinLayer);
	
	virtual bool init() override;

    virtual void onMessage(int notify_id, const net_data_t& root) override;

private:
	cocos2d::Node* load_csd();

	void onClickCupboard(Ref* sender);
	void onClickReturn(Ref* sender);


private:
	ImageView* m_Image_1;
	Text* m_cur_score;
	Text* m_Text_1_0_0;
	Text* m_Text_1_0;
	Text* m_cur_time;
	Text* m_highest;
	Text* m_Text_1;

};

#endif

