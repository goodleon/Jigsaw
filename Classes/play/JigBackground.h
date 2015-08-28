//
//  JigBackground.h
//  Jigsaw
//
//  Created by zhangdw on 15-8-18.
//
//

#ifndef __Jigsaw__JigBackground__
#define __Jigsaw__JigBackground__

#include "PlayShared.h"

class JigBackground : public Layer
{
public:
    JigBackground();
    virtual ~JigBackground() override;
    
    CREATE_FUNC(JigBackground);
    
    virtual bool init() override;
    
    void reset(SpriteFrame* jigsaw, int rows, int cols);
    
private:
    Sprite* m_jigsaw;
};

#endif /* defined(__Jigsaw__JigBackground__) */
