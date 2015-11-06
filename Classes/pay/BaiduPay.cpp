//
//  BaiduPay.cpp
//  Jigsaw
//
//  Created by zhangdw on 15-11-6.
//
//

#include "BaiduPay.h"

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include <jni.h>


void BaiduPay::init()
{

}
void BaiduPay::exit()
{

}

//单位是分
void BaiduPay::pay(int money)
{
    JniMethodInfo info;
    bool ret = JniHelper::getStaticMethodInfo(info,"org/cocos2dx/cpp/BaiduPay","pay","(I)V");
    if(ret)
    {
        CCLOG("zz:call android BaiduPay pay");
        info.env->CallStaticVoidMethod(info.classID,info.methodID, money);
    }
}

#endif