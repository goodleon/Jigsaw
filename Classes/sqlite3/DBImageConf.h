
#ifndef __Jigsaw__DBImageConf__
#define __Jigsaw__DBImageConf__

#include "string"

class DBImageConf
{
public:
	int id;
	int rows;
	int cols;
	int rot;

    DBImageConf();
    
    //static DBImageConf readby_level(int level);
    static DBImageConf readby_id(int id);
    static DBImageConf readby_condition(const std::string& con);
private:
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);
};

#endif /* defined(__Jigsaw__DBImageConf__) */
