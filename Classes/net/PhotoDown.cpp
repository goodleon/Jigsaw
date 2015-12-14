//
//  PhotoDown.cpp
//  Jigsaw
//
//  Created by zhangdw on 15-12-8.
//
//

#include "PhotoDown.h"
#include "ProtoId.h"
#include "arpa/inet.h"
#include "DBImage.h"
#include "JigNotify.h"
#include "JigToast.h"

//static const string g_img_dir = "img/";
string PhotoDown::get_full_img(const string& img)
{
    return FileUtils::getInstance()->getWritablePath() + "img/" + img;
}

PhotoDown::PhotoDown()
{
    string img_dir = FileUtils::getInstance()->getWritablePath() + "img/";
    if(!FileUtils::getInstance()->isDirectoryExist(img_dir))
    {
        FileUtils::getInstance()->createDirectory(img_dir);
    }
    m_loading = false;
}

PhotoDown::~PhotoDown()
{

}

void PhotoDown::load(int photo_id)
{
    set<int> photo_ids;
    photo_ids.insert(photo_id);
    load_many(photo_ids);
}

void PhotoDown::load_many(const set<int>& photo_ids)
{
    addPath(photo_ids);

    if (!m_loading) {
        loadPatch();
    }
}

void PhotoDown::addPath(const set<int>& photo_ids)
{
    m_ready.push_back(photo_ids);
}

void PhotoDown::loadPatch()
{
    if(m_ready.empty())
        return;

    set<int> photo_ids = m_ready.front();
    string ids;
    for (auto it=photo_ids.begin(); it!=photo_ids.end(); ++it){
        DBImage item = DBImage::readby_id(*it);
        if (FileUtils::getInstance()->isFileExist( get_full_img(item.name))) {
            m_ready.front().erase(*it);
        }
        else{
            ids += sstr("%d,", *it);
        }
    }
    if (ids.empty()) {
        finishPatch();
        return;
    }

    Request req(proto_download_img_up);
    req.append("img_ids", ids);
    string buf = req.to_string();

    HttpRequest* postRequest = new HttpRequest();
    postRequest->setRequestType( HttpRequest::Type::POST );
    postRequest->setUrl("http://localhost:8000/cgi-bin/proto.cmd");
    postRequest->setResponseCallback(&PhotoDown::onHttpResponse);
    postRequest->setRequestData(buf.c_str(), buf.length());

    HttpClient* httpClient = HttpClient::getInstance();
    httpClient->setTimeoutForConnect(10);
    httpClient->setTimeoutForRead(10);
    httpClient->send(postRequest);
    postRequest->release();
}

void PhotoDown::finishPatch()
{
    rapidjson::Document doc;
    doc.SetObject();
    if (!m_ready.front().empty()) {
        JigNotify::inst().notifyListener(notify_img_failed_one, doc);
    }
    else{
        JigNotify::inst().notifyListener(notify_img_complete_one, doc);
    }
    m_ready.erase( m_ready.begin() );
}

void PhotoDown::onHttpResponse(HttpClient* client, HttpResponse* response)
{
    if (!response->isSucceed()) {
        CCLOG("PhotoDown:%s", response->getErrorBuffer());
        return;
    }

    const vector<char>* data = response->getResponseData();
    if (data->size()<9) {
        return;
    }

    int top0 = ntohl( *(int*)(&data->front()) );
    int top1 = ntohl( *(int*)(&data->front()+4) );
    if (top0==0 && top1==0)//此时代表出错
    {
        net_data_t doc;
        string err(data->begin()+9, data->end());
        doc.Parse<0>(err.c_str());
        JigNotify::inst().notifyListener(doc["proto"].GetInt(), doc);
    }
    else
    {
        const char* head = &data->front();
        while (head<&data->back())
        {
            int img_id = ntohl( *(int*)(head) );
            int img_size = ntohl( *(int*)(head+4) );

            if (img_id==0 && img_size==0)//此时代表出错
            {
                net_data_t doc;
                string err(head+9, &data->back());
                doc.Parse<0>(err.c_str());
                JigToast::show(doc["msg"].GetString());
                head = &data->back();
//                JigNotify::inst().notifyListener(doc["proto"].GetInt(), doc);
            }
            else
            {
                DBImage db = DBImage::readby_id(img_id);
                if(db.id>0)
                {
                    string file = get_full_img(db.name);
                    FILE* fp = fopen(file.c_str(), "wb");
                    if (fp)
                    {
                        fwrite(head+9, img_size, 1, fp);
                        fclose(fp);

                        PhotoDown::inst().m_ready.front().erase(img_id);
                    }
                }
            }

            head += sizeof(img_id)+sizeof(img_size)+1+img_size+1;
        }
        
        PhotoDown::inst().finishPatch();
    }
}
