//
//  PaymentMgr.h
//  Jigsaw
//
//  Created by zhangdw on 15-11-6.
//
//

#ifndef __Jigsaw__PaymentMgr__
#define __Jigsaw__PaymentMgr__

#include "PayInterface.h"
#include "cex.h"

class PaymentMgr : public cex::Singleton<PaymentMgr>
{
public:
    PaymentMgr();
    ~PaymentMgr();

    void init();
    void exit();

    void pay(int money);

    void setPayCallback(std::function<void(bool)> fun);
    void onPayResult(bool succeed);
private:
    PayInterface* m_pay;
    std::function<void(bool)> m_payCallback;
};

#endif /* defined(__Jigsaw__PaymentMgr__) */
