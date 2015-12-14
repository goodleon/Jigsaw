
#ifndef __Jigsaw__DBVersion__
#define __Jigsaw__DBVersion__

#include "string"

class DBVersion
{
public:
	int version;

    DBVersion();
    
    //static DBVersion readby_level(int level);
    static DBVersion readby_id(int id);
    static DBVersion readby_condition(const std::string& con);
private:
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);
};

#endif /* defined(__Jigsaw__DBVersion__) */
