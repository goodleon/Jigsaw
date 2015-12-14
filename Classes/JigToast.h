

#ifndef __Jigsaw_JigToast_
#define __Jigsaw_JigToast_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class JigToast : public cocos2d::Layer
{
public:
	JigToast();
	virtual ~JigToast() override;

    static void show(const std::string& lan_id);
    static void show_raw(const std::string& text);
private:
    CREATE_FUNC(JigToast);
	
	virtual bool init() override;

private:
	cocos2d::Node* load_csd();



private:
    cocos2d::ui::Text* m_text;

};

#endif

