

#ifndef __Jigsaw_LevelPassItem_
#define __Jigsaw_LevelPassItem_

#include "JigHeader.h"
#include "DBLevelNotes.h"

class LevelPassItem : public cocos2d::ui::Widget
{
public:
	LevelPassItem();
	virtual ~LevelPassItem() override;

	CREATE_FUNC(LevelPassItem);
	
	virtual bool init() override;

    void reset(const DBLevelNotes& item);

private:
	cocos2d::Node* load_csd();

	void onClickButton(Ref* sender);


private:
	ImageView* m_star2;
	ImageView* m_star1;
	ImageView* m_star0;
	Text* m_level;

};

#endif

