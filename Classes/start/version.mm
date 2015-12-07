//
//  version.mm
//  Jigsaw
//
//  Created by zhangdw on 15-11-2.
//
//

#if CC_TARGET_PLATFORM==CC_PLATFORM_MAC || CC_TARGET_PLATFORM==CC_PLATFORM_IOS

#include "version.h"
#import <Foundation/Foundation.h>
std::string get_version()
{
    NSString* str = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"];
    return [str cStringUsingEncoding:NSUTF8StringEncoding];
}

#endif