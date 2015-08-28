

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

    bool canEnter();

private:
	vector<ImageView*> m_stars;
	Text* m_level;
    DBLevelNotes m_data;
};

#endif

