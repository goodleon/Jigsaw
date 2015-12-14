
#include "DBVersion.h"
#include "sqlite3.h"
#include "cex.h"
#include "cocos2d.h"
#include "sql_common.h"

using namespace std;
using namespace cex;
USING_NS_CC;

DBVersion::DBVersion()
{
	version = 0;
}

// DBVersion DBVersion::readby_level(int level)
// {
//     DBVersion data;

//     string file = jigsql::database_file();
//     sqlite3* db;
//     int rc = sqlite3_open(file.c_str(), &db);
//     if( rc ){
//         CCLOG("Can't open database: %s\n", file.c_str());
//         sqlite3_close(db);
//         return data;
//     }
//     char *zErrMsg = 0;
//     rc = sqlite3_exec(db, cstr("select * from Version where level=%d", level), DBVersion::callback, &data, &zErrMsg);
//     if( rc!=SQLITE_OK ){
//         CCLOG("SQL error: %s\n", zErrMsg);
//         sqlite3_free(zErrMsg);
//     }
//     sqlite3_close(db);
//     return data;
// }

DBVersion DBVersion::readby_id(int id)
{
    DBVersion data;

    string file = jigsql::database_file();
    sqlite3* db;
    int rc = sqlite3_open(file.c_str(), &db);
    if( rc ){
        CCLOG("Can't open database: %s\n", file.c_str());
        sqlite3_close(db);
        return data;
    }
    char *zErrMsg = 0;
    rc = sqlite3_exec(db, cstr("select * from Version where id=%d", id), DBVersion::callback, &data, &zErrMsg);
    if( rc!=SQLITE_OK ){
        CCLOG("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
    return data;
}

DBVersion DBVersion::readby_condition(const string& con)
{
    DBVersion data;

    string file = jigsql::database_file();
    sqlite3* db;
    int rc = sqlite3_open(file.c_str(), &db);
    if( rc ){
        CCLOG("Can't open database: %s\n", file.c_str());
        sqlite3_close(db);
        return data;
    }
    char *zErrMsg = 0;
    rc = sqlite3_exec(db, cstr("select * from Version where %s", con.c_str()), DBVersion::callback, &data, &zErrMsg);
    if( rc!=SQLITE_OK ){
        CCLOG("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
    return data;
}

int DBVersion::callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    DBVersion* data = static_cast<DBVersion*>(NotUsed);

	data->version = atoi(argv[0]);

	return 0;
}
