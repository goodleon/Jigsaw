//
//  Network.cpp
//  Jigsaw
//
//  Created by zhangdw on 15-12-7.
//
//

#include "Network.h"
#include "JigNotify.h"

Network::Network()
{

}

Network::~Network()
{
    
}

void Network::addRequest(const Request& request)
{
    std::string buf = request.to_string();
//    CCLOG("发送:%s", buf.c_str());

    HttpRequest* postRequest = new HttpRequest();
    postRequest->setRequestType( HttpRequest::Type::POST );
    postRequest->setUrl("http://localhost:8000/cgi-bin/proto.cmd");
    postRequest->setResponseCallback(&Network::onHttpResponse);
    postRequest->setRequestData(buf.c_str(), buf.length());

    HttpClient* httpClient = HttpClient::getInstance();
    httpClient->setTimeoutForConnect(10);
    httpClient->setTimeoutForRead(10);
    httpClient->send(postRequest);
    postRequest->release();
}

void Network::onHttpResponse(HttpClient* client, HttpResponse* response)
{
    if (!response->isSucceed()) {
        CCLOG("error:%s", response->getErrorBuffer());
        net_data_t data;
        data.SetObject();
        data.AddMember("msg", response->getErrorBuffer(), data.GetAllocator());
        JigNotify::inst().notifyListener(proto_net_error, data);
        return;
    }

    string res_string(response->getResponseData()->begin(), response->getResponseData()->end());
    rapidjson::Document doc;
    doc.Parse<0>( res_string.c_str() );

//    CCLOG("response:%s", res_string.c_str());

    if (!doc.IsObject() || !doc.HasMember("proto")) {
        CCLOG("error: no proto");
        return;
    }

    JigNotify::inst().notifyListener(doc["proto"].GetInt(), doc);
}
