#!/usr/bin/python
#encoding=utf8

import cgi, json
import struct
import db

print "Content-Type:text/html"
print ""

recv = cgi.FieldStorage()
# print json.dumps({"proto":1000})
obj = json.loads(recv['json'].value)

try:
	proto = obj['proto']
	userid = obj['userid']
	if  proto==10000: #刷新history
		db.refreshHistory(userid)
		img_ids = ''
		conf_ids = ''
		passes = ''
		for item in db.getHistoryByUid(userid, obj["refreshType"]):
			img_ids += '%d,'%(item[2])
			conf_ids += '%d,'%(item[3])
			passes += '%d,'%(item[4])
		print json.dumps({"img_ids":img_ids, "conf_ids":conf_ids, "passes":passes,"proto":50001})
	elif proto==10001: #取得history
		img_ids = ''
		conf_ids = ''
		passes = ''
		for item in db.getHistoryByUid(userid, obj["refreshType"]):
			img_ids += '%d,'%(item[2])
			conf_ids += '%d,'%(item[3])
			passes += '%d,'%(item[4])
		print json.dumps({"img_ids":img_ids, "conf_ids":conf_ids, "passes":passes,"proto":50001})
	elif proto==10002: #下载图片
		try:
			for id in obj['img_ids'].split(','):
				if id=='': continue
				id = int(id)
				data = open(db.getImageNameById(id), 'rb').read()
				print struct.pack('>II', id, len(data)), data
		except Exception as e:
			print struct.pack('>II', 0, 0), json.dumps({'proto':50005, 'msg':str(e)})
	elif proto==10003: #客户端登陆
		if db.getUser(userid) is None:
			userid = db.create_user()
		print json.dumps({'proto':50003, 'userid':userid})
	elif proto==10004: #检查网络状况
		print json.dumps({'proto':50004})
	elif proto==10005: #取得ChooseLayer的图片
		prce = db.getProcessImgId(userid);
		print json.dumps({'proto':50006, 'img_id':prce[2], 'conf_id':prce[3], 'start_time':prce[4],'pass':prce[5]})
	elif proto==10006:
		prce = db.refreshProcessImgId(userid);
		print json.dumps({'proto':50006, 'img_id':prce[2], 'conf_id':prce[3], 'start_time':prce[4],'pass':prce[5]})
	elif proto==10007:
		db.enterGameScene(userid, obj['conf_id'])
		print json.dumps({'proto':50007});
	elif proto==10008:
		db.startPlaying(userid)
		print json.dumps({'proto':50008})
	elif proto==10009:
		used_time = db.winPlaying(userid)
		print json.dumps({'proto':50009,'used_time':used_time})
	elif proto==10010:
		high_score,use_time,cur_score = db.playEndWin(userid)
		print json.dumps({'proto':50010, 'highest':high_score, 'used_time':use_time, 'cur_score':cur_score})
	else:
		print json.dumps({'proto':50005, 'msg':"无法识别的协议号:%d"%(proto)})
except Exception as e:
	print json.dumps({'proto':50005, 'msg':str(e)})
























		