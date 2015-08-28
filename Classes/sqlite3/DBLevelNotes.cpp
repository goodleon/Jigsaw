//
//  DBLevelNotes.cpp
//  Jigsaw
//
//  Created by zhangdw on 15-8-26.
//
//

#include "DBLevelNotes.h"
#include "sqlite3.h"
#include "cex.h"
#include "cocos2d.h"
#include "sql_common.h"

using namespace std;
using namespace cex;
USING_NS_CC;

DBLevelNotes::DBLevelNotes()
{
    level = 0;
    star = 0;
    score = 0;
}

bool DBLevelNotes::readby_level(DBLevelNotes& data, int level, int jiglevel)
{
    string file = jigsql::database_file();
    sqlite3* db;
    int rc = sqlite3_open(file.c_str(), &db);
    if( rc ){
        CCLOG("Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return false;
    }
    char *zErrMsg = 0;
    rc = sqlite3_exec(db, cstr("select * from LevelNotes where level=%d and jiglevel=%d", level, jiglevel), DBLevelNotes::callback, &data, &zErrMsg);
    if( rc!=SQLITE_OK ){
        CCLOG("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return false;
    }
    sqlite3_close(db);
    return true;
}

void DBLevelNotes::writeby_level()
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
    rc = sqlite3_exec(db, cstr("update LevelNotes set star=%d ,score=%d where level==%d and jiglevel=%d", star, score, level, jiglevel), nullptr, nullptr, &zErrMsg);
    if( rc!=SQLITE_OK ){
        CCLOG("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
}

int DBLevelNotes::callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    DBLevelNotes* data = (DBLevelNotes*)NotUsed;
    data->id = atoi( argv[0] );
    data->level = atoi( argv[1] );
    data->jiglevel = atoi( argv[2] );
    data->star = atoi( argv[3] );
    data->score = atoi( argv[4] );
    return 0;
}