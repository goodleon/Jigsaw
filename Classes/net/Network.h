//
//  Network.h
//  Jigsaw
//
//  Created by zhangdw on 15-12-7.
//
//

#ifndef __Jigsaw__Network__
#define __Jigsaw__Network__

#include "JigHeader.h"
#include "ProtoId.h"
#include "network/HttpClient.h"
#include "network/HttpRequest.h"
#include "Request.h"

USING_NS_CC;
using namespace cocos2d::network;

class Network : public Singleton<Network>
{
public:
    Network();
    ~Network();

    void addRequest(const Request& request);
protected:

    static void onHttpResponse(HttpClient* client, HttpResponse* response);
};

#endif /* defined(__Jigsaw__Network__) */
