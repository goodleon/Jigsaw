//
//  DBJigLevel.h
//  Jigsaw
//
//  Created by zhangdw on 15-8-26.
//
//

#ifndef __Jigsaw__DBJigLevel__
#define __Jigsaw__DBJigLevel__

class DBJigLevel
{
public:
    int id;
    int level;
    int rows;
    int cols;
    
    DBJigLevel();
    
    static bool readby_level(DBJigLevel& data, int level);
private:
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);
};

#endif /* defined(__Jigsaw__DBJigLevel__) */
