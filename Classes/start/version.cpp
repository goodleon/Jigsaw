//
//  version.mm
//  Jigsaw
//
//  Created by zhangdw on 15-11-2.
//
//

#include "version.h"

std::string get_version()
{
    return "1.0";
//    NSString* str = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"];
//    return [str cStringUsingEncoding:NSUTF8StringEncoding];
}