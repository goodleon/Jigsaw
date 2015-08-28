//
//  Direction.cpp
//  Jigsaw
//
//  Created by zhangdw on 15-8-21.
//
//

#include "Direction.h"



Direction::Direction()
:m_dir(DT_UP)
{
    
}

Direction::Direction(DirectionType dir)
:m_dir(dir)
{
    
}

Direction::~Direction()
{
    
}

int Direction::toint()
{
    return m_dir;
}

Direction Direction::next()
{
    return Direction( (DirectionType)((m_dir+1)%4) );
}

