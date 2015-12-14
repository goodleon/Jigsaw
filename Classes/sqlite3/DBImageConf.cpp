
#include "DBImageConf.h"
#include "sqlite3.h"
#include "cex.h"
#include "cocos2d.h"
#include "sql_common.h"

using namespace std;
using namespace cex;
USING_NS_CC;

DBImageConf::DBImageConf()
{
	id = 0;
	rows = 0;
	cols = 0;
	rot = 0;
}

// DBImageConf DBImageConf::readby_level(int level)
// {
//     DBImageConf data;

//     string file = jigsql::database_file();
//     sqlite3* db;
//     int rc = sqlite3_open(file.c_str(), &db);
//     if( rc ){
//         CCLOG("Can't open database: %s\n", file.c_str());
//         sqlite3_close(db);
//         return data;
//     }
//     char *zErrMsg = 0;
//     rc = sqlite3_exec(db, cstr("select * from ImageConf where level=%d", level), DBImageConf::callback, &data, &zErrMsg);
//     if( rc!=SQLITE_OK ){
//         CCLOG("SQL error: %s\n", zErrMsg);
//         sqlite3_free(zErrMsg);
//     }
//     sqlite3_close(db);
//     return data;
// }

DBImageConf DBImageConf::readby_id(int id)
{
    DBImageConf data;

    string file = jigsql::database_file();
    sqlite3* db;
    int rc = sqlite3_open(file.c_str(), &db);
    if( rc ){
        CCLOG("Can't open database: %s\n", file.c_str());
        sqlite3_close(db);
        return data;
    }
    char *zErrMsg = 0;
    rc = sqlite3_exec(db, cstr("select * from ImageConf where id=%d", id), DBImageConf::callback, &data, &zErrMsg);
    if( rc!=SQLITE_OK ){
        CCLOG("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
    return data;
}

DBImageConf DBImageConf::readby_condition(const string& con)
{
    DBImageConf data;

    string file = jigsql::database_file();
    sqlite3* db;
    int rc = sqlite3_open(file.c_str(), &db);
    if( rc ){
        CCLOG("Can't open database: %s\n", file.c_str());
        sqlite3_close(db);
        return data;
    }
    char *zErrMsg = 0;
    rc = sqlite3_exec(db, cstr("select * from ImageConf where %s", con.c_str()), DBImageConf::callback, &data, &zErrMsg);
    if( rc!=SQLITE_OK ){
        CCLOG("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
    return data;
}

int DBImageConf::callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    DBImageConf* data = static_cast<DBImageConf*>(NotUsed);

	data->id = atoi(argv[0]);
	data->rows = atoi(argv[1]);
	data->cols = atoi(argv[2]);
	data->rot = atoi(argv[3]);

	return 0;
}
