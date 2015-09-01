//
//  DBLevelNotes.h
//  Jigsaw
//
//  Created by zhangdw on 15-8-26.
//
//

#ifndef __Jigsaw__DBLevelNotes__
#define __Jigsaw__DBLevelNotes__

class DBLevelNotes
{
public:
    int id;
    int level;
    int jiglevel;
    int star;
    int score;
    
    DBLevelNotes();
    
    static DBLevelNotes readby_level(int level, int jiglevel);
    void writeby_level();
private:
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);
};

#endif /* defined(__Jigsaw__DBLevelNotes__) */
