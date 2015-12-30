//
//  sql_common.cpp
//  Jigsaw
//
//  Created by zhangdw on 15-8-28.
//
//

#include "sql_common.h"
#include "stdio.h"
#include "sqlite3.h"

void jigsql::copy_database()
{
#if CC_TARGET_PLATFORM!=CC_PLATFORM_MAC
    const string db_pack = FileUtils::getInstance()->fullPathForFilename("database.db");
//    const int pack_version = get_database_version_number( db_pack );
//    const int writable_version = get_database_version_number( database_file() );
//    if (pack_version > writable_version)
    if (!FileUtils::getInstance()->isFileExist(database_file())) {
        copy_database_nocheck(db_pack, "writable.db");
    }
#endif
}

string jigsql::database_file()
{
#if CC_TARGET_PLATFORM!=CC_PLATFORM_MAC
    return FileUtils::getInstance()->getWritablePath() + "writable.db";
#else
    return FileUtils::getInstance()->fullPathForFilename("database.db");
#endif
}

void jigsql::copy_database_nocheck(const string& src_file, const string& dst_file)
{
    Data data = FileUtils::getInstance()->getDataFromFile(src_file);
    string dst = FileUtils::getInstance()->getWritablePath() + dst_file;
    FILE* fp = fopen(dst.c_str(), "w");
    if (fp)
    {
        fwrite(data.getBytes(), data.getSize(), 1, fp);
        fclose(fp);
    }
}

int read_version_callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    if (argc>0)
    {
        int* version = (int*)NotUsed;
        *version = atoi(argv[0]);
    }
    return 0;
}
int jigsql::get_database_version_number(const string& db_file)
{
    int version = 0;

    sqlite3* db;
    int rc = sqlite3_open(db_file.c_str(), &db);
    if( rc )//打不开
    {
        return UserDefault::getInstance()->getIntegerForKey("sql_version");
    }
    else
    {
        char* error = nullptr;
        rc = sqlite3_exec(db, "select * from Version", read_version_callback, (void*)&version, &error);
        if( rc!=SQLITE_OK )
        {
            sqlite3_free(error);
        }
    }
    sqlite3_close(db);
    return version;
}