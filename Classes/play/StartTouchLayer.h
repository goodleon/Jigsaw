//
//  StartTouchLayer.h
//  Jigsaw
//
//  Created by zhangdw on 15-8-25.
//
//

#ifndef __Jigsaw__StartTouchLayer__
#define __Jigsaw__StartTouchLayer__

#include "PlayShared.h"

class StartTouchLayer : public cocos2d::Layer
{
public:
    StartTouchLayer();
    ~StartTouchLayer();
    
    CREATE_FUNC(StartTouchLayer);
    
    virtual bool init() override;
    
private:
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
};

#endif /* defined(__Jigsaw__StartTouchLayer__) */
