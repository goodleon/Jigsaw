

#ifndef __Jigsaw__TouchPanel__
#define __Jigsaw__TouchPanel__

#include "PlayShared.h"
#include "JigTile.h"
#include "TouchPanelEvent.h"

class TouchPanel : public cocos2d::Sprite
{
public:
    friend class TouchPanelEventListener;

	TouchPanel();
	virtual ~TouchPanel();
    
    virtual bool init();

    void reset(const string& file, int rows, int cols);
    virtual void setStartRect(const Rect& rc);
    
    bool isAllFinished();

    JigTile* getTouchingTile();

    void manageEvent(TouchPanelEventListener* event);
    void notifyEvent(TouchPanelEvent event);
protected:
    virtual void onClickTile(Touch* touch) = 0;
    virtual void onDragBegan(Touch* touch) = 0;
    virtual void onDragMoved(Touch* touch) = 0;
    virtual void onDragEnded(Touch* touch) = 0;
    virtual void startTile(int index, const Point& pt) = 0;

    void resortTiles();

    vector<JigTile*> m_tiles;
    JigTile* m_touching;
    
    Size m_tileSize;
    int m_splitRows;
    int m_splitCols;

    vector<TouchPanelEventListener*> m_events;
private:
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    
    void clear();

    void initTiles(const string& gif_file);
    void initEdges();
    void initBackLines();
    
    void longTouchCallback(float delay);

    void startGame();
    void checkGameState();
    bool canTouch();
private:
    enum TouchType
    {
        Touch_None
       ,Touch_Drag
    }m_touch_type;
};

#endif /* defined(__Jigsaw__TouchPanel__) */

