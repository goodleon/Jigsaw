
#ifndef __Jigsaw__DBRecord__
#define __Jigsaw__DBRecord__

#include "string"

class DBRecord
{
public:
	int id;
	int img_id;
	int img_conf;

    DBRecord();
    
    //static DBRecord readby_level(int level);
    static DBRecord readby_id(int id);
    static DBRecord readby_condition(const std::string& con);
private:
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);
};

#endif /* defined(__Jigsaw__DBRecord__) */
