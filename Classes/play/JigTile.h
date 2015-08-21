//
//  JigTile.h
//  Jigsaw
//
//  Created by zhangdw on 15-8-17.
//
//

#ifndef __Jigsaw__JigTile__
#define __Jigsaw__JigTile__

#include "PlayShared.h"
#include "TempShadow.h"
#include "Direction.h"

class JigTile : public cocos2d::ClippingNode
{
public:
    JigTile();
    virtual ~JigTile();
    
    CREATE_FUNC(JigTile);
    
    virtual bool init() override;
    
    void setRawFrame(SpriteFrame* frame);
    void setRawRect(const Rect& rc);
    
    void setEdges(const std::vector<EdgeType>& edges);
    std::vector<EdgeType> getEdges();
    
    void setDirection(Direction dir);
    Direction getDirection();
    
private:
    Sprite* m_display;
    
};

#endif /* defined(__Jigsaw__JigTile__) */
