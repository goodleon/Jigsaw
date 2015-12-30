#encoding=utf-8
import sqlite3 as db

header_temp = '''
#ifndef __Jigsaw__${class}__
#define __Jigsaw__${class}__

#include "string"

class ${class}
{
public:
${variable}
    ${class}();
    
    //static ${class} readby_level(int level);
    static ${class} readby_id(int id);
    static ${class} readby_condition(const std::string& con);
private:
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);
};

#endif /* defined(__Jigsaw__${class}__) */
'''

cpp_temp = '''
#include "${class}.h"
#include "sqlite3.h"
#include "cex.h"
#include "cocos2d.h"
#include "sql_common.h"

using namespace std;
using namespace cex;
USING_NS_CC;

${class}::${class}()
{
${var_init}}

// ${class} ${class}::readby_level(int level)
// {
//     ${class} data;

//     string file = jigsql::database_file();
//     sqlite3* db;
//     int rc = sqlite3_open(file.c_str(), &db);
//     if( rc ){
//         CCLOG("Can't open database: %s\\n", file.c_str());
//         sqlite3_close(db);
//         return data;
//     }
//     char *zErrMsg = 0;
//     rc = sqlite3_exec(db, cstr("select * from ${table_name} where level=%d", level), ${class}::callback, &data, &zErrMsg);
//     if( rc!=SQLITE_OK ){
//         CCLOG("SQL error: %s\\n", zErrMsg);
//         sqlite3_free(zErrMsg);
//     }
//     sqlite3_close(db);
//     return data;
// }

${class} ${class}::readby_id(int id)
{
    ${class} data;

    string file = jigsql::database_file();
    sqlite3* db;
    int rc = sqlite3_open(file.c_str(), &db);
    if( rc ){
        CCLOG("Can't open database: %s\\n", file.c_str());
        sqlite3_close(db);
        return data;
    }
    char *zErrMsg = 0;
    rc = sqlite3_exec(db, cstr("select * from ${table_name} where id=%d", id), ${class}::callback, &data, &zErrMsg);
    if( rc!=SQLITE_OK ){
        CCLOG("SQL error: %s\\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
    return data;
}

${class} ${class}::readby_condition(const string& con)
{
    ${class} data;

    string file = jigsql::database_file();
    sqlite3* db;
    int rc = sqlite3_open(file.c_str(), &db);
    if( rc ){
        CCLOG("Can't open database: %s\\n", file.c_str());
        sqlite3_close(db);
        return data;
    }
    char *zErrMsg = 0;
    rc = sqlite3_exec(db, cstr("select * from ${table_name} where %s", con.c_str()), ${class}::callback, &data, &zErrMsg);
    if( rc!=SQLITE_OK ){
        CCLOG("SQL error: %s\\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
    return data;
}

int ${class}::callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    ${class}* data = static_cast<${class}*>(NotUsed);

${var_assign}
	return 0;
}
'''

con = db.connect('../../Resources/database.db')
cur = con.cursor()

def dataType(src):
	candy = {"INTEGER":"int", "integer(128)":"int", "integer":"int", "char(128)":"std::string"}
	if src in candy:
		return candy[src]
	else:
		return src

def table2header(table):
	class_name = 'DB%s'%(table)

	variable = ''
	for x in cur.execute('PRAGMA table_info(%s)'%(table)):
		variable += '\t%s %s;\n'%(dataType(x[2]), x[1])
	
	tmp = header_temp.replace('${class}', class_name)
	tmp = tmp.replace('${variable}', variable)
	return tmp

# def defValue(type):
# 	candy = {"int":"0"}
def assian_exp(data_name, data_type, index):
	if data_type=="int":
		return '\tdata->%s = atoi(argv[%d]);\n'%(data_name, index)
	elif data_type=="float":
		return '\tdata->%s = atof(argv[%d]);\n'%(data_name, index)
	else:
		return '\tdata->%s = argv[%d];\n'%(data_name, index)

def table2cpp(table):
	class_name = 'DB%s'%(table)

	var_init = ''
	for x in cur.execute('PRAGMA table_info(%s)'%(table)):
		if dataType(x[2])=='int':
			var_init += '\t%s = 0;\n'%(x[1], )

	var_assign = ''
	for x in cur.execute('PRAGMA table_info(%s)'%(table)):
		var_assign += assian_exp(x[1], dataType(x[2]), x[0])

	tmp = cpp_temp.replace('${class}', class_name)
	tmp = tmp.replace('${var_init}', var_init)
	tmp = tmp.replace('${var_assign}', var_assign)
	tmp = tmp.replace('${table_name}', table)
	return tmp

def main():
	# for tb in cur.execute('select * from sqlite_master where type=\"table\"'):
	# 	print tb[1]
	# return 
	cur = con.cursor()
	for tb in cur.execute('select * from sqlite_master where type=\"table\"'):
		table_name = tb[1]
		if table_name in ["sqlite_sequence"]: 
			print 'ignore', table_name
			continue;
		fheader = open('DB%s.h'%(table_name), "w")
		fheader.write( table2header(table_name) )
		fheader.close()

		fcpp = open('DB%s.cpp'%(table_name), "w")
		fcpp.write( table2cpp(table_name) )
		fcpp.close()

		print 'finished', table_name
main()
# print table2cpp('Version')
# print table2cpp('MainLevel')
# print table2cpp('Record')







