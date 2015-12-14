//
//  PhotoDown.h
//  Jigsaw
//
//  Created by zhangdw on 15-12-8.
//
//

#ifndef __Jigsaw__PhotoDown__
#define __Jigsaw__PhotoDown__

#include "JigHeader.h"
#include "HttpClient.h"
#include "HttpRequest.h"
#include "Request.h"

using namespace network;

class PhotoDown : public cex::Singleton<PhotoDown>
{
public:
    PhotoDown();
    ~PhotoDown();

    void load(int photo_id);
    void load_many(const set<int>& photo_ids);

    static string get_full_img(const string& img);
private:
    void addPath(const set<int>& photo_ids);
    void loadPatch();
    void finishPatch();
//    void download(int photo_id, const string& local_path);

    static void onHttpResponse(HttpClient* client, HttpResponse* response);
private:
    vector< set<int> > m_ready;
    bool m_loading;
};

#endif /* defined(__Jigsaw__PhotoDown__) */
