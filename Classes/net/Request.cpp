//
//  Request.cpp
//  Jigsaw
//
//  Created by zhangdw on 15-12-8.
//
//

#include "Request.h"
#include "ClientCenter.h"

Request::Request(int arg_proto)
{
    m_proto = arg_proto;
    m_doc.SetObject();
    this->append("proto", m_proto);
    this->append("userid", ClientCenter::inst().user_id);
}

int Request::proto() const
{
    return m_proto;
}

std::string Request::to_string() const
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    m_doc.Accept(writer);
    return string("json=")+buffer.GetString();
}