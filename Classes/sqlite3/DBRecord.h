//
//  DBRecord.h
//  Jigsaw
//
//  Created by zhangdw on 15-8-26.
//
//

#ifndef __Jigsaw__DBRecord__
#define __Jigsaw__DBRecord__

#include "string"

class DBRecord
{
public:
    int id;
    int main_level;
    int sub_level;
    
    DBRecord();
    
    static DBRecord readby_level(int level);

    void write();
private:
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);
};

#endif /* defined(__Jigsaw__DBRecord__) */
