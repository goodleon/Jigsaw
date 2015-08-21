

#ifndef __Jigsaw__DragonlyTouchPanel__
#define __Jigsaw__DragonlyTouchPanel__

#include "TouchPanel.h"

class DragonlyTouchPanel : public TouchPanel
{
public:
	DragonlyTouchPanel();
	virtual ~DragonlyTouchPanel();
    
    CREATE_FUNC(DragonlyTouchPanel);
    
protected:
    virtual void onClickTile(Touch* touch) override;
    virtual void onDragBegan(Touch* touch) override;
    virtual void onDragMoved(Touch* touch) override;
    virtual void onDragEnded(Touch* touch) override;
    
    void selectTile(JigTile* tile);
private:
    Point m_touchOffset;
};

#endif /* defined(__Jigsaw__DragonlyTouchPanel__) */

