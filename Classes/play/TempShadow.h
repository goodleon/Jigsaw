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
USING_NS_CC;

enum EdgeType
{
    ET_V,
    ET_F,
    ET_A
};

class TempShadow : public ClippingNode
{
public:
    TempShadow();
    virtual ~TempShadow() override;
    
    static TempShadow* create();
    
    virtual bool init();
    
    void setSquareSize(const Size& size);
    Size getSquareSize();
    Size getFullSize();
    
    void setEdgeType(std::vector<EdgeType>& edges);
    
private:
    void configCircle(Sprite* circle, int index);
    Node* createSubCircles(std::vector<EdgeType>& edges);
private:
    Sprite* m_square;
};

#endif /* defined(__Jigsaw__TempShadow__) */
