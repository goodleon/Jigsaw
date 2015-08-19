//
//  ChooseScene.h
//  Jigsaw
//
//  Created by zhangdw on 15-8-17.
//
//

#ifndef __Jigsaw__ChooseLayer__
#define __Jigsaw__ChooseLayer__

#include "cocos2d.h"

class ChooseLayer : public cocos2d::Layer
{
public:
    ChooseLayer();
    virtual ~ChooseLayer();
    
    CREATE_FUNC(ChooseLayer);
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
private:
    
    void onStartClick(cocos2d::Ref* button);
    
};

#endif /* defined(__Jigsaw__ChooseScene__) */
