//
//  JigLayer.h
//  Jigsaw
//
//  Created by zhangdw on 15-12-3.
//
//

#ifndef __Jigsaw__JigLayer__
#define __Jigsaw__JigLayer__

#include "cocos2d.h"

class JigLayer : public cocos2d::Layer
{
public:
    JigLayer();
    virtual ~JigLayer();

    virtual void onExit() override;

    std::function<void(cocos2d::Layer*)> onExitEvent;
};

#endif /* defined(__Jigsaw__JigLayer__) */
