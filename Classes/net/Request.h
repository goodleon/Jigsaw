//
//  Request.h
//  Jigsaw
//
//  Created by zhangdw on 15-12-8.
//
//

#ifndef __Jigsaw__Request__
#define __Jigsaw__Request__

#include "JigHeader.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

static string server_addr = "192.168.130.246";
static string get_server_addr(){
    return sstr("http://%s:8000/cgi-bin/proto.py", server_addr.c_str());
}

class Request
{
public:
    Request(int arg_proto);

    template<class T>
    void append(const std::string& key, const T& value){
        CCASSERT(!m_doc.HasMember(key.c_str()), "");
        rapidjson::Value name(key.c_str(), m_doc.GetAllocator());
        rapidjson::Value val(value);
        m_doc.AddMember(name, val, m_doc.GetAllocator());
    }

    void append(const std::string& key, const string& value){
        CCASSERT(!m_doc.HasMember(key.c_str()), "");
        rapidjson::Value name(key.c_str(), m_doc.GetAllocator());
        rapidjson::Value val(value.c_str(), m_doc.GetAllocator());
        m_doc.AddMember(name, val, m_doc.GetAllocator());
    }

    int proto() const;

    std::string to_string() const;

private:
    int m_proto;
    rapidjson::Document m_doc;
};


#endif /* defined(__Jigsaw__Request__) */