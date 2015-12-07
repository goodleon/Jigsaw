//
//  sql_common.h
//  Jigsaw
//
//  Created by zhangdw on 15-8-28.
//
//

#ifndef __Jigsaw__sql_common__
#define __Jigsaw__sql_common__

#include "JigHeader.h"

namespace jigsql
{
    void copy_database();

    string database_file();

    void copy_database_nocheck(const string& src_file, const string& dst_file);
    int get_database_version_number(const string& db_file);
}



#endif /* defined(__Jigsaw__sql_common__) */
