//
//  DBMainLevel.h
//  Jigsaw
//
//  Created by zhangdw on 15-8-26.
//
//

#ifndef __Jigsaw__DBMainLevel__
#define __Jigsaw__DBMainLevel__

class DBMainLevel
{
public:
    int id;
    int level;
    int min_jiglevel;
    int max_jiglevel;
    
    DBMainLevel();
    
    static bool readby_level(DBMainLevel& data, int level);
private:
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);
};

#endif /* defined(__Jigsaw__DBMainLevel__) */
