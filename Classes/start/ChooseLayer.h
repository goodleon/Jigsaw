

#ifndef __Jigsaw_ChooseLayer_
#define __Jigsaw_ChooseLayer_

#include "JigHeader.h"
#include "JigRadio.h"
#include "jig_tools.h"

struct ImageInfo
{
    int img_id;
    int conf_id;
};

class ChooseLayer : public cocos2d::Layer
{
public:
    JIG_SCENE_FROM_LAYER(ChooseLayer);
    
private:
	ChooseLayer();
	virtual ~ChooseLayer() override;

	CREATE_FUNC(ChooseLayer);

	virtual bool init() override;

    void initRadio();

    void refreshImg();
    void refreshConfig();
    void updateConfig();
    
private:
	cocos2d::Node* load_csd();

    void onClickSplitBar(Ref* sender);
    void onClickStart(Ref* sender);
    void onClickNext(Ref* sender);
    void onClickLast(Ref* sender);
    void onClickNewest(Ref* sender);
    void onClickReturn(Ref* sender);

private:
    TextAtlas* m_level;
    CheckBox* m_check_rot;
    Text* m_Text_1_0;
    Text* m_Text_1_0_0_0_0;
    Text* m_Text_1_0_0;
    Text* m_Text_1_0_0_0;
    Text* m_score;
    ImageView* m_img_bg;
    Text* m_Text_6;
    CheckBox* m_check1;
    CheckBox* m_check2;
    CheckBox* m_check3;
    CheckBox* m_check0;
    Text* m_Text_1;

private:
    JigRadio m_radio;

    ImageInfo m_info;
};

#endif

