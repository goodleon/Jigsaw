
#include "DBImage.h"
#include "sqlite3.h"
#include "cex.h"
#include "cocos2d.h"
#include "sql_common.h"

using namespace std;
using namespace cex;
USING_NS_CC;

DBImage::DBImage()
{
	id = 0;
}

// DBImage DBImage::readby_level(int level)
// {
//     DBImage data;

//     string file = jigsql::database_file();
//     sqlite3* db;
//     int rc = sqlite3_open(file.c_str(), &db);
//     if( rc ){
//         CCLOG("Can't open database: %s\n", file.c_str());
//         sqlite3_close(db);
//         return data;
//     }
//     char *zErrMsg = 0;
//     rc = sqlite3_exec(db, cstr("select * from Image where level=%d", level), DBImage::callback, &data, &zErrMsg);
//     if( rc!=SQLITE_OK ){
//         CCLOG("SQL error: %s\n", zErrMsg);
//         sqlite3_free(zErrMsg);
//     }
//     sqlite3_close(db);
//     return data;
// }

DBImage DBImage::readby_id(int id)
{
    DBImage data;

    string file = jigsql::database_file();
    sqlite3* db;
    int rc = sqlite3_open(file.c_str(), &db);
    if( rc ){
        CCLOG("Can't open database: %s\n", file.c_str());
        sqlite3_close(db);
        return data;
    }
    char *zErrMsg = 0;
    rc = sqlite3_exec(db, cstr("select * from Image where id=%d", id), DBImage::callback, &data, &zErrMsg);
    if( rc!=SQLITE_OK ){
        CCLOG("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
    return data;
}

DBImage DBImage::readby_condition(const string& con)
{
    DBImage data;

    string file = jigsql::database_file();
    sqlite3* db;
    int rc = sqlite3_open(file.c_str(), &db);
    if( rc ){
        CCLOG("Can't open database: %s\n", file.c_str());
        sqlite3_close(db);
        return data;
    }
    char *zErrMsg = 0;
    rc = sqlite3_exec(db, cstr("select * from Image where %s", con.c_str()), DBImage::callback, &data, &zErrMsg);
    if( rc!=SQLITE_OK ){
        CCLOG("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
    return data;
}

int DBImage::callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    DBImage* data = static_cast<DBImage*>(NotUsed);

	data->id = atoi(argv[0]);
	data->name = argv[1];

	return 0;
}
