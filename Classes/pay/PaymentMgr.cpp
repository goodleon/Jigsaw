//
//  PaymentMgr.cpp
//  Jigsaw
//
//  Created by zhangdw on 15-11-6.
//
//

#define Pay_Baidu

#include "PaymentMgr.h"
#include "BaiduPay.h"

PaymentMgr::PaymentMgr()
:m_pay(nullptr)
,m_payCallback(nullptr)
{
#ifdef Pay_Baidu
    m_pay = new BaiduPay();
#endif
}

PaymentMgr::~PaymentMgr()
{
    delete m_pay;
    m_pay = nullptr;
}

void PaymentMgr::init()
{
    if (!m_pay)
        return;
    m_pay->init();
}

void PaymentMgr::exit()
{
    if (!m_pay)
        return;
    m_pay->exit();
}

void PaymentMgr::pay(int money)
{
    if (!m_pay)
        return;
    m_pay->pay(money);
}

void PaymentMgr::onPayResult(bool succeed)
{
    if (m_payCallback) {
        m_payCallback(succeed);
        m_payCallback = nullptr;
    }
}

void PaymentMgr::setPayCallback(std::function<void(bool)> fun)
{
    m_payCallback = fun;
}