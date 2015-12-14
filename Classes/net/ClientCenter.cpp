//
//  ClientCenter.cpp
//  Jigsaw
//
//  Created by zhangdw on 15-12-8.
//
//

#include "ClientCenter.h"
#include "PhotoDown.h"
#include "NetErrorLayer.h"
#include "GameSceneMgr.h"
#include "Network.h"
#include "JigToast.h"

ClientCenter::ClientCenter()
{
    JigNotify::inst().addListener(this);

    user_id = UserDefault::getInstance()->getIntegerForKey("userid");
//    login = false;
}

ClientCenter::~ClientCenter()
{
    JigNotify::inst().removeListener(this);
}

void ClientCenter::onMessage(int notify_id, const net_data_t& root)
{
    if (notify_id == proto_net_error)
    {
        if (GameSceneMgr::inst().curScene()) {
            if (!m_net_error) {
                m_net_error = NetErrorLayer::create();
                GameSceneMgr::inst().curScene()->addChild( m_net_error );
            }
            m_net_error->setErrorMessage(root["msg"].GetString());
        }
        else{
            Request req(proto_login_up);
            Network::inst().addRequest(req);
        }
    }
    else if (notify_id == proto_login_down)
    {
        user_id = root["userid"].GetInt();
        UserDefault::getInstance()->setIntegerForKey("userid", user_id);
    }
    else if (notify_id == proto_check_network_down)
    {
        if (m_net_error) {
            GameSceneMgr::inst().curScene()->removeChild(m_net_error);
            m_net_error = nullptr;
        }
//        Request req(proto_login_up);
//        Network::inst().addRequest(req);
    }
}


