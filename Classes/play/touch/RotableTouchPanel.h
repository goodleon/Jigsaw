

#ifndef __Jigsaw__RotableTouchPanel__
#define __Jigsaw__RotableTouchPanel__

#include "DragonlyTouchPanel.h"

class RotableTouchPanel : public DragonlyTouchPanel
{
public:
	RotableTouchPanel();
	virtual ~RotableTouchPanel();
    
    CREATE_FUNC(RotableTouchPanel);
    
protected:
    void onClickTile(Touch* touch);
};

#endif /* defined(__Jigsaw__RotableTouchPanel__) */

