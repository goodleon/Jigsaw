//
//  Direction.h
//  Jigsaw
//
//  Created by zhangdw on 15-8-21.
//
//

#ifndef __Jigsaw__Direction__
#define __Jigsaw__Direction__

#include <stdio.h>

enum DirectionType
{
    DT_UP,
    DT_RIGHT,
    DT_DOWN,
    DT_LEFT
};

class Direction
{
public:
    Direction();
    Direction(DirectionType dir);
    ~Direction();
    
    friend bool operator == (const Direction& dir1, DirectionType dir2){
        return dir1.m_dir==dir2;
    }
    
    int toint();
    Direction next();
    
private:
    DirectionType m_dir;
};


#endif /* defined(__Jigsaw__Direction__) */
