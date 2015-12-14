//
//  ProtoId.h
//  Jigsaw
//
//  Created by zhangdw on 15-12-7.
//
//

#ifndef Jigsaw_ProtoId_h
#define Jigsaw_ProtoId_h


static const int proto_error = 0;

static const int proto_history_refresh_up       = 10000; //history请求刷新
static const int proto_history_getinfo_up       = 10001; //请求history数据
static const int proto_download_img_up          = 10002; //客户端请求下载图片
static const int proto_login_up                 = 10003; //客户端登陆
static const int proto_check_network_up         = 10004; //检查网络状况
static const int proto_get_progress_up          = 10005; //取得ChooseLayer的图片
static const int proto_refresh_progress_up      = 10006; //跳过ChooseLayer的图片
static const int proto_enter_gamescene_up       = 10007; //点击开始按钮
static const int proto_start_playing_up         = 10008; //开始拖动图片
static const int proto_start_play_win_up        = 10009; //已经胜利
static const int proto_start_play_end_up        = 10010; //点击完成按钮

static const int proto_history_refresh_down     = 50001; //history返回刷新
static const int proto_download_img_down        = 50002; //服务器请求下载文件
static const int proto_login_down               = 50003; //客户端登陆
static const int proto_check_network_down       = 50004; //检查网络状况
static const int proto_net_error                = 50005; //服务器发生异常
static const int proto_get_progress_down        = 50006; //回复ChooseLayer的图片
static const int proto_enter_gamescene_down     = 50007; //点击开始按钮
static const int proto_start_playing_down       = 50008; //开始拖动图片
static const int proto_start_play_win_down      = 50009; //已经胜利
static const int proto_start_play_end_down      = 50010; //点击完成按钮

static const int notify_img_complete_one        = 100000; //下载完图片
static const int notify_img_failed_one          = 100001; //下载图片失败


#endif
