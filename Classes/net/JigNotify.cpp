//
//  JigNotify.cpp
//  Jigsaw
//
//  Created by zhangdw on 15-12-8.
//
//

#include "JigNotify.h"

NotifyListener::NotifyListener(bool autoJoin)
{
    if (autoJoin)
    {
        JigNotify::inst().addListener(this);
    }
}
NotifyListener::~NotifyListener()
{
    JigNotify::inst().removeListener(this);
}

JigNotify::JigNotify()
{

}

JigNotify::~JigNotify()
{

}

void JigNotify::addListener(NotifyListener* listener)
{
    m_listener.insert(listener);
}
void JigNotify::removeListener(NotifyListener* listener)
{
    m_listener.erase(listener);
}

void JigNotify::notifyListener(int proto, const net_data_t& root)
{
    CCLOG("JigNotify:%d", proto);
    for (auto it = m_listener.begin(); it != m_listener.end(); ++it)
    {
        (*it)->onMessage(proto, root);
    }
}