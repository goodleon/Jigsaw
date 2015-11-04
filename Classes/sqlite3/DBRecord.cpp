//
//  DBRecord.cpp
//  Jigsaw
//
//  Created by zhangdw on 15-8-26.
//
//

#include "DBRecord.h"
#include "sqlite3.h"
#include "cex.h"
#include "cocos2d.h"
#include "sql_common.h"

using namespace std;
using namespace cex;
USING_NS_CC;

DBRecord::DBRecord()
{
    id = 0;
    main_level = 0;
    sub_level = 0;
}

DBRecord DBRecord::readby_level(int level)
{
    DBRecord data;

    string file = jigsql::database_file();
    sqlite3* db;
    int rc = sqlite3_open(file.c_str(), &db);
    if( rc ){
        CCLOG("Can't open database: %s\n", file.c_str());
        sqlite3_close(db);
        return data;
    }
    char *zErrMsg = 0;
    rc = sqlite3_exec(db, cstr("select * from Record where level=%d", level), DBRecord::callback, &data, &zErrMsg);
    if( rc!=SQLITE_OK ){
        CCLOG("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
    return data;
}

void DBRecord::write()
{
    string file = jigsql::database_file();
    sqlite3* db;
    int rc = sqlite3_open(file.c_str(), &db);
    if( rc ){
        CCLOG("Can't open database: %s\n", file.c_str());
        sqlite3_close(db);
        return;
    }
    char *zErrMsg = 0;
    string sql = sstr("update Record set sub_level=%d where id=%d", sub_level, id);
    rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &zErrMsg);
    if( rc!=SQLITE_OK ){
        CCLOG("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
}

int DBRecord::callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    DBRecord* data = (DBRecord*)NotUsed;
    data->id = atoi( argv[0] );
    data->main_level = atoi( argv[1] );
    data->sub_level = atoi( argv[2] );
    return 0;
}