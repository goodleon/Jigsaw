import sqlite3 as sql
import time
con = sql.connect('server.db')

def getImageNameById(id):
	cur = con.cursor()
	cur.execute('select name from Image where id=%d'%(id))
	return 'img/'+cur.fetchall()[0][0]

# def create_new_history(uid):
# 	cmd_img = 'select * from Image ORDER by id limit 6'
# 	cmd_img = runSql(cmd_img).fetchall()
# 	cmd_conf = [1, 1, 3, 3, 5, 7]
# 	for i in xrange(0,6):
# 		cmd = 'insert into History(user_id,img_id,img_conf_id,pass) values(%d,%d,%d,0)'%(uid,cmd_img[i][0],cmd_conf[i])
# 		runSql(cmd)
def create_new_process(uid):
	cmd = 'insert into Process(user_id,img_id,conf_id,start_time,pass) values(%d,1,1,0,0)'%(uid)
	runSql(cmd)
def create_user():
	t = time.time()
	userid=runSql("insert into User(create_time) values(%f)"%(t)).lastrowid
	create_new_process(userid)
	return userid
def getHistoryByUid(uid, type):
	cmd = "select * from History where user_id=%d"%(uid)
	return runSql(cmd).fetchall()

def getUser(uid):
	data =runSql('select * from User where id=%d'%(uid)).fetchall()
	if len(data)==0:
		return None
	else:
		return data[0]

# def refreshHistory(uid):
# 	cmd_img = 'select * from Image ORDER by random() limit 6'
# 	cmd_conf = 'select * from ImageConf ORDER by random() limit 6'
# 	cmd_img = runSql(cmd_img).fetchall()
# 	cmd_conf = runSql(cmd_conf).fetchall()
# 	for i in xrange(0,6):
# 		cmd = 'update History set img_id=%d,img_conf_id=%d,pass=0 where user_id=%d and pass=1'%(cmd_img[i][0],cmd_conf[i][0],uid)
# 		runSql(cmd)

def getProcessImgId(uid):
	cmd = 'select * from Process where user_id=%d'%(uid)
	return runSql(cmd).fetchall()[0]
def refreshProcessImgId(uid):
	img = runSql('select * from Image ORDER by random() limit 1').fetchall()[0]
	process = getProcessImgId(uid)
	while img[0]==process[2]:
		img = runSql('select * from Image ORDER by random() limit 1').fetchall()[0]
	cmd = 'update Process set img_id=%d,conf_id=3,start_time=0,pass=0'%(img[0])
	runSql(cmd)
	return getProcessImgId(uid)
def enterGameScene(userid, conf_id):
	cmd = 'update Process set conf_id=%d where user_id=%d'%(conf_id, userid)
	runSql(cmd)
def startPlaying(uid):
	start_time = time.time()
	cmd = 'update Process set start_time=%f where user_id=%d'%(start_time, uid)
	runSql(cmd)
def winPlaying(uid):
	cur_time = time.time()
	last = runSql('select start_time from Process where user_id=%d'%(uid)).fetchall()[0][0]
	runSql('update Process set end_time=%f where user_id=%d'%(cur_time,uid) )
	return cur_time-last;
def calcScore(his_item):
	conf = his_item[3]
	use_time = his_item[5]
	conf = runSql('select * from ImageConf where id=%d'%(conf)).fetchall()[0]
	score = int(conf[1])*100
	if int(conf[3])==1:
		score = score*2
	if use_time>=100:
		score = score+0
	else:
		score = score+int(100-use_time)*10
	return score
def sortWithConfig(arg1, arg2):
	score1, score2 = calcScore(arg1),calcScore(arg2)
	if score1<score2: return -1
	elif score1>score2: return 1
	else: return 0;
def playEndWin(uid):
	runSql('update Process set pass=1 where user_id=%d'%(uid) )
	pro = runSql('select * from Process where user_id=%d'%(uid)).fetchall()[0]
	valus = '%d,%d,%d,%f,%f'%(uid,pro[2],pro[3],pro[4],pro[6]-pro[4])
	runSql('insert into History(user_id,img_id,img_conf_id,start_time,used_time) values(%s)'%(valus))
	maxitems = runSql('select * from History where user_id=%d'%(uid)).fetchall()
	maxitems.sort(cmp=lambda x,y:sortWithConfig(x,y), reverse=True)
	his_cur = (0,uid,pro[2],pro[3],pro[4],pro[6]-pro[4])
	return (calcScore(maxitems[0]), pro[6]-pro[4], calcScore(his_cur))
def runSql(cmd):
	cur = con.cursor()
	ret =  cur.execute(cmd)
	con.commit()
	return ret

def query(cmd):
	cur = con.cursor()
	return cur.execute(cmd).fetchall()

if __name__ == '__main__':
	pass
	# global con
	# con = sql.connect('../server.db')
	# print getImageNameById(1)
	# runSql('insert into History values(1, 1000, )')
	# print query('select * from Image')
	# for x in xrange(8,33):
	# 	name = 'img%d.jpg'%(x)
	# 	print 'insert into Image(name) values(\"%s\")'%(name)
	# 	runSql('insert into Image(name) values(\"%s\")'%(name))