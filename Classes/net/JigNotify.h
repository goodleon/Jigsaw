//
//  JigNotify.h
//  Jigsaw
//
//  Created by zhangdw on 15-12-8.
//
//

#ifndef __Jigsaw__JigNotify__
#define __Jigsaw__JigNotify__

#include "JigHeader.h"
#include "ProtoId.h"

typedef rapidjson::Document net_data_t;


class NotifyListener
{
public:
    NotifyListener(bool autoJoin=true);
    virtual ~NotifyListener();
    virtual void onMessage(int notify_id, const net_data_t& root) = 0;
};

class JigNotify : public cex::Singleton<JigNotify>
{
public:
    JigNotify();
    ~JigNotify();

    void addListener(NotifyListener* listener);
    void removeListener(NotifyListener* listener);

    void notifyListener(int proto, const net_data_t& root);

private:
    std::set<NotifyListener*> m_listener;
};

#endif /* defined(__Jigsaw__JigNotify__) */
