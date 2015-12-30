
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
	img_id = 0;
	img_conf = 0;
}

// DBRecord DBRecord::readby_level(int level)
// {
//     DBRecord data;

//     string file = jigsql::database_file();
//     sqlite3* db;
//     int rc = sqlite3_open(file.c_str(), &db);
//     if( rc ){
//         CCLOG("Can't open database: %s\n", file.c_str());
//         sqlite3_close(db);
//         return data;
//     }
//     char *zErrMsg = 0;
//     rc = sqlite3_exec(db, cstr("select * from Record where level=%d", level), DBRecord::callback, &data, &zErrMsg);
//     if( rc!=SQLITE_OK ){
//         CCLOG("SQL error: %s\n", zErrMsg);
//         sqlite3_free(zErrMsg);
//     }
//     sqlite3_close(db);
//     return data;
// }

DBRecord DBRecord::readby_id(int id)
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
    rc = sqlite3_exec(db, cstr("select * from Record where id=%d", id), DBRecord::callback, &data, &zErrMsg);
    if( rc!=SQLITE_OK ){
        CCLOG("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
    return data;
}

DBRecord DBRecord::readby_condition(const string& con)
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
    rc = sqlite3_exec(db, cstr("select * from Record where %s", con.c_str()), DBRecord::callback, &data, &zErrMsg);
    if( rc!=SQLITE_OK ){
        CCLOG("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
    return data;
}

int DBRecord::callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    DBRecord* data = static_cast<DBRecord*>(NotUsed);

	data->id = atoi(argv[0]);
	data->img_id = atoi(argv[1]);
	data->img_conf = atoi(argv[2]);

	return 0;
}
