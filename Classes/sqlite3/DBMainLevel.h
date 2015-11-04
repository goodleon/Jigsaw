//
//  DBMainLevel.h
//  Jigsaw
//
//  Created by zhangdw on 15-8-26.
//
//

#ifndef __Jigsaw__DBMainLevel__
#define __Jigsaw__DBMainLevel__

#include "string"

class DBMainLevel
{
public:
    int id;
    int level;
    int Count;
    bool Rotable;
    std::string Description;
    
    DBMainLevel();
    
    static DBMainLevel readby_level(int level);
private:
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);
};

#endif /* defined(__Jigsaw__DBMainLevel__) */
