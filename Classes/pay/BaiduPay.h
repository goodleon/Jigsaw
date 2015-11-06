//
//  BaiduPay.h
//  Jigsaw
//
//  Created by zhangdw on 15-11-6.
//
//

#ifndef __Jigsaw__BaiduPay__
#define __Jigsaw__BaiduPay__

#include "PayInterface.h"

class BaiduPay : public PayInterface
{
public:
    BaiduPay();
    ~BaiduPay();

    virtual void init() override;
    virtual void exit() override;

    //单位是分
    virtual void pay(int money) override;
};

#endif /* defined(__Jigsaw__BaiduPay__) */
