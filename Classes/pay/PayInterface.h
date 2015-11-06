//
//  PayInterface.h
//  Jigsaw
//
//  Created by zhangdw on 15-11-6.
//
//

#ifndef __Jigsaw__PayInterface__
#define __Jigsaw__PayInterface__

#include <stdio.h>

class PayInterface
{
public:
    PayInterface(){};
    virtual ~PayInterface(){};

    virtual void init() = 0;
    virtual void exit() = 0;

    //单位是分
    virtual void pay(int money) = 0;
};

#endif /* defined(__Jigsaw__PayInterface__) */
