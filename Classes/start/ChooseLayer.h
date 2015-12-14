

#ifndef __Jigsaw_ChooseLayer_
#define __Jigsaw_ChooseLayer_

#include "JigHeader.h"
#include "JigRadio.h"
#include "jig_tools.h"
#include "JigNotify.h"

struct ImageInfo
{
    int img_id;
    int conf_id;
    int start_time;
    bool pass;
};

class ChooseLayer : public cocos2d::Layer , public NotifyListener
{
public:
    JIG_SCENE_FROM_LAYER(ChooseLayer);
    
private:
	ChooseLayer();
	virtual ~ChooseLayer() override;

	CREATE_FUNC(ChooseLayer);

	virtual bool init() override;

    void refreshImg();
    void refreshConfig();

    virtual void onMessage(int notify_id, const net_data_t& root) override;
private:
	cocos2d::Node* load_csd();

	void onClickReturn(Ref* sender);
	void onClickSplitBar(Ref* sender);
    void onClickStart(Ref* sender);
    void onClickJump(Ref* sender);
    
    void initRadio();
    void updateScore();
private:
    CheckBox* m_check_rot;
    Text* m_Text_1_0_0_0_0;
    Text* m_score;
    Text* m_Text_1_0_0;
    Text* m_Text_1_0_0_0;
    ImageView* m_img_bg;
    Text* m_Text_6;
    Text* m_Text_1_0;
    Text* m_Text_1;
    CheckBox* m_check2;
    CheckBox* m_check3;
    CheckBox* m_check0;
    CheckBox* m_check1;

private:
    JigRadio m_radio;

    ImageInfo m_info;
};

#endif

