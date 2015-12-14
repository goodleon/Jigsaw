from sqlite3 import *

con = connect('server.db')
cur = con.cursor()
print cur.execute("insert into User(name,create_time) values('z','w')").lastrowid
print con.commit()