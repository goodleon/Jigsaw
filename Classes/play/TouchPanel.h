

#ifndef __Jigsaw__TouchPanel__
#define __Jigsaw__TouchPanel__

#include "PlayShared.h"
#include "JigTile.h"

class TouchPanel : public cocos2d::Sprite
{
public:
	TouchPanel();
	virtual ~TouchPanel();
    
    CREATE_FUNC(TouchPanel);
    
    virtual bool init();

    void reset(cocos2d::SpriteFrame* sf, int rows, int cols);

private:
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    
//    void resetTiles();
    void clear();
    
//    Point cocos2array(int x, int y);
private:
    
    vector<JigTile*> m_tiles;
    JigTile* m_touching;
    Point m_touchOffset;
    
    Size m_tileSize;
    int m_splitRows;
    int m_splitCols;
};

#endif /* defined(__Jigsaw__TouchPanel__) */

