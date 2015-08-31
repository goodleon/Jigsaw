//
//  TempShadow.h
//  Jigsaw
//
//  Created by zhangdw on 15-8-18.
//
//

#ifndef __Jigsaw__TempShadow__
#define __Jigsaw__TempShadow__

#include "cocos2d.h"
#include "ShadowCommand.h"
USING_NS_CC;

class TempShadow : public Sprite
{
public:
    TempShadow();
    virtual ~TempShadow() override;
    
    CREATE_FUNC(TempShadow);
    
    virtual bool init();
    
    void setSquareSize(const Size& size);
    Size getSquareSize();
    float getSquareScale();
    
    void setEdgeType(const std::vector<EdgeType>& edges);
    std::vector<EdgeType> getEdgeType();

private:
    float m_scale;
    Sprite* m_shadow;
    std::vector<EdgeType> m_edges;
};

#endif /* defined(__Jigsaw__TempShadow__) */
