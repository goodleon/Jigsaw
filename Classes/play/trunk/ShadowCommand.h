//
//  ShadowCommand.h
//  Jigsaw
//
//  Created by zhangdw on 15-8-20.
//
//

#ifndef __Jigsaw__ShadowCommand__
#define __Jigsaw__ShadowCommand__

#include "cocos2d.h"
#include "string"

using namespace std;
USING_NS_CC;

enum EdgeType
{
    ET_V,
    ET_F,
    ET_A
};

class ShadowCommand
{
public:
    static Sprite* createShadowByEdges(const std::vector<EdgeType>& edges);
};

#endif /* defined(__Jigsaw__ShadowCommand__) */
