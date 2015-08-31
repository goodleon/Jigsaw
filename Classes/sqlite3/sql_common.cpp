//
//  sql_common.cpp
//  Jigsaw
//
//  Created by zhangdw on 15-8-28.
//
//

#include "sql_common.h"

void jigsql::copy_database()
{
#if CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID
    string name = FileUtils::getInstance()->fullPathForFilename("database.db");
    Data data = FileUtils::getInstance()->getDataFromFile(name);

    string dst = FileUtils::getInstance()->getWritablePath() + "writable.db";
    if (!FileUtils::getInstance()->isFileExist(dst))
    {
        FILE* fp = fopen(dst.c_str(), "w");
        if (fp)
        {
            fwrite(data.getBytes(), data.getSize(), 1, fp);
            fclose(fp);
        }
    }
#endif
}

string jigsql::database_file()
{
#if CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID
    return FileUtils::getInstance()->getWritablePath() + "writable.db";
#else
    return FileUtils::getInstance()->fullPathForFilename("database.db");
#endif
}

