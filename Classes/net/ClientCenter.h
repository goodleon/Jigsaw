//
//  ClientCenter.h
//  Jigsaw
//
//  Created by zhangdw on 15-12-8.
//
//

#ifndef __Jigsaw__ClientCenter__
#define __Jigsaw__ClientCenter__

#include "JigHeader.h"
#include "JigNotify.h"

class NetErrorLayer;

class ClientCenter : public cex::Singleton<ClientCenter>, public NotifyListener
{
public:
    ClientCenter();
    ~ClientCenter();

    virtual void onMessage(int notify_id, const net_data_t& root);

    int user_id;
//    bool login;

private:
    NetErrorLayer* m_net_error;
};

#endif /* defined(__Jigsaw__ClientCenter__) */
