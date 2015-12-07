//
//  version.mm
//  Jigsaw
//
//  Created by zhangdw on 15-11-2.
//
//

#if CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID
#include "version.h"
#include "platform/android/jni/JniHelper.h"
//#include <jni.h>
USING_NS_CC;
std::string get_version()
{
	JniMethodInfo info;
    bool ret=JniHelper::getStaticMethodInfo(info,"org/cocos2dx/cpp/JigHelper","get_version","()");
    if(ret)
    {
        jstring hint = (jstring)info.env->CallStaticObjectMethod(info.classID,info.methodID, nullptr);

		const char *str = info.env->GetStringUTFChars( hint, NULL);
        std::string version = str ? str : "0.0";
        info.env->ReleaseStringUTFChars(hint, str);

		return version;
    }
    return "0.0";
}

#endif