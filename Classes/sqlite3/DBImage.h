
#ifndef __Jigsaw__DBImage__
#define __Jigsaw__DBImage__

#include "string"

class DBImage
{
public:
	int id;
	std::string name;

    DBImage();
    
    //static DBImage readby_level(int level);
    static DBImage readby_id(int id);
    static DBImage readby_condition(const std::string& con);
private:
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);
};

#endif /* defined(__Jigsaw__DBImage__) */
