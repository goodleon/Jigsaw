//
//  DBJigLevel.cpp
//  Jigsaw
//
//  Created by zhangdw on 15-8-26.
//
//

#include "DBJigLevel.h"
#include "sqlite3.h"
#include "cex.h"
#include "cocos2d.h"
#include "sql_common.h"

using namespace std;
using namespace cex;
USING_NS_CC;

DBJigLevel::DBJigLevel()
{
    id = 0;
    level = 0;
    rows = 0;
    cols = 0;
}

bool DBJigLevel::readby_level(DBJigLevel& data, int level)
{
    string file = jigsql::database_file();
    sqlite3* db;
    int rc = sqlite3_open(file.c_str(), &db);
    if( rc ){
        CCLOG("Can't open database: %s\n", file.c_str());
        sqlite3_close(db);
        return false;
    }
    char *zErrMsg = 0;
    rc = sqlite3_exec(db, cstr("select * from JigLevel where level=%d", level), DBJigLevel::callback, &data, &zErrMsg);
    if( rc!=SQLITE_OK ){
        CCLOG("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return false;
    }
    sqlite3_close(db);
    return true;
}

int DBJigLevel::callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    DBJigLevel* data = (DBJigLevel*)NotUsed;
    data->id = atoi( argv[0] );
    data->level = atoi( argv[1] );
    data->rows = atoi( argv[2] );
    data->cols = atoi( argv[3] );
    return 0;
}