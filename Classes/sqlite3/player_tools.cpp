//
//  player_tools.cpp
//  Jigsaw
//
//  Created by zhangdw on 15-12-29.
//
//

#include "player_tools.h"
#include "jig_sys_conf.h"
#include "sqlite3.h"

using namespace std;
using namespace player_tools;

int player_tools::get_next_imgid()
{
    const int img_id = get_max_finished_imgid();
    return (img_id==0||img_id==total_img_number) ? 1 : img_id+1;
}

int player_tools::get_max_finished_imgid()
{
    string con = "img_id=(select max(img_id) from Record)";
    DBRecord rd = DBRecord::readby_condition(con);
    return rd.img_id;
}

bool player_tools::check_save_record(const DBRecord& rd)
{
    bool ret = true;

    DBRecord has = DBRecord::readby_condition( sstr("img_id=%d", rd.img_id) );
    string file = jigsql::database_file();
    sqlite3* db;
    int rc = sqlite3_open(file.c_str(), &db);
    CCASSERT(rc==0, "");
    if (has.id==0)
    {
        string cmd = sstr("insert into Record(img_id, img_conf) values(%d,%d)",rd.img_id, rd.img_conf);
        rc = sqlite3_exec(db, cmd.c_str(), nullptr, nullptr, nullptr);
    }
    else if ( player_tools::calc_score(rd.img_conf)>player_tools::calc_score(has.img_conf) )
    {
        string cmd = sstr("update Record set img_id=%d,img_conf=%d",rd.img_id, rd.img_conf);
        rc = sqlite3_exec(db, cmd.c_str(), nullptr, nullptr, nullptr);
    }
    else
    {
        ret = false;
    }
    CCASSERT(rc==SQLITE_OK, "");

    sqlite3_close(db);

    return ret;
}

int player_tools::calc_score(int image_conf)
{
    if (image_conf==0) {
        return 0;
    }
    else{
        int score = (image_conf-1)/2*150 + 300; //0,1,2,3
        score *= image_conf%2==0 ? 2 : 1;
        return score;
    }
}


