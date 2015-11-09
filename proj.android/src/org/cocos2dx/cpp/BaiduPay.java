package org.cocos2dx.cpp;

import org.json.JSONObject;

import com.duoku.platform.single.DKPlatform;
import com.duoku.platform.single.DkErrorCode;
import com.duoku.platform.single.DkProtocolKeys;
import com.duoku.platform.single.callback.IDKSDKCallBack;
import com.duoku.platform.single.item.GamePropsInfo;


import android.util.Log;
import android.widget.Toast;

public class BaiduPay {
	public static native void onPayResult(boolean result);
	
	public static void pay(int money){
		Log.v("zz", "wwwwwww");
		
		IDKSDKCallBack RechargeCallback = new IDKSDKCallBack(){
			AppActivity activity = AppActivity.self;
			@Override
			public void onResponse(String paramString) {
				// TODO Auto-generated method stub
				try {
					JSONObject jsonObject = new JSONObject(paramString);
					// 支付状态码
					int mStatusCode = jsonObject.getInt(DkProtocolKeys.FUNCTION_STATUS_CODE);
					
					if(mStatusCode == DkErrorCode.BDG_RECHARGE_SUCCESS){
						// 返回支付成功的状态码，开发者可以在此处理相应的逻辑
						
						// 订单ID
						String mOrderId = null;
						// 订单状态
						String mOrderStatus = null;
						// 道具ID
						String mOrderProductId = null;
						// 道具价格
						String mOrderPrice = null;
						// 支付通道
						String mOrderPayChannel = null;
						
						if(jsonObject.has(DkProtocolKeys.BD_ORDER_ID)){						
							mOrderId = jsonObject.getString(DkProtocolKeys.BD_ORDER_ID);	
//							SharedUtil.getInstance(GamePropsActivity.this).saveString(SharedUtil.PAYMENT_ORDERID, mOrderId);
						}
						if(jsonObject.has(DkProtocolKeys.BD_ORDER_STATUS)){
							mOrderStatus = jsonObject.getString(DkProtocolKeys.BD_ORDER_STATUS);
						}
						if(jsonObject.has(DkProtocolKeys.BD_ORDER_PRODUCT_ID)){			
							mOrderProductId = jsonObject.getString(DkProtocolKeys.BD_ORDER_PRODUCT_ID);
						}
						if(jsonObject.has(DkProtocolKeys.BD_ORDER_PAY_CHANNEL)){						
							mOrderPayChannel = jsonObject.getString(DkProtocolKeys.BD_ORDER_PAY_CHANNEL);
						}
						if(jsonObject.has(DkProtocolKeys.BD_ORDER_PRICE)){						
							mOrderPrice = jsonObject.getString(DkProtocolKeys.BD_ORDER_PRICE);
						}
						
//						int mNum = Integer.valueOf(mOrderPrice) * 10;
//						String propsType = "1";
						Toast.makeText(activity, "道具购买成功!\n金额:"+mOrderPrice+"元", Toast.LENGTH_LONG).show();
						
						onPayResult(true);
//						DemoRecordData data = new DemoRecordData(mOrderProductId, mOrderPrice, propsType, String.valueOf(mNum));
//						DemoDBDao.getInstance(activity).updateRechargeRecord(data);
						
					}else if(mStatusCode == DkErrorCode.BDG_RECHARGE_USRERDATA_ERROR){
						
						Toast.makeText(activity, "用户透传数据不合法", Toast.LENGTH_LONG).show();
						
						onPayResult(false);
					}else if(mStatusCode == DkErrorCode.BDG_RECHARGE_ACTIVITY_CLOSED){
						
						// 返回玩家手动关闭支付中心的状态码，开发者可以在此处理相应的逻辑
						Toast.makeText(activity, "玩家关闭支付中心", Toast.LENGTH_LONG).show();
						
						onPayResult(false);
					}else if(mStatusCode == DkErrorCode.BDG_RECHARGE_FAIL){ 
						if(jsonObject.has(DkProtocolKeys.BD_ORDER_ID)){			
//							SharedUtil.getInstance(GamePropsActivity.this).saveString(SharedUtil.PAYMENT_ORDERID, jsonObject.getString(DkProtocolKeys.BD_ORDER_ID));
						}
						// 返回支付失败的状态码，开发者可以在此处理相应的逻辑
						Toast.makeText(activity, "购买失败", Toast.LENGTH_LONG).show();
						
						onPayResult(false);
					} else if(mStatusCode == DkErrorCode.BDG_RECHARGE_EXCEPTION){ 
						
						// 返回支付出现异常的状态码，开发者可以在此处理相应的逻辑
						Toast.makeText(activity, "购买出现异常", Toast.LENGTH_LONG).show();
						
						onPayResult(false);
					} else if(mStatusCode == DkErrorCode.BDG_RECHARGE_CANCEL){ 
						
						// 返回取消支付的状态码，开发者可以在此处理相应的逻辑
						Toast.makeText(activity, "玩家取消支付", Toast.LENGTH_LONG).show();
						
						onPayResult(false);
					} else {
						Toast.makeText(activity, "未知情况", Toast.LENGTH_LONG).show();
						
						onPayResult(false);
					}
					
				} catch (Exception e) {
					// TODO: handle exception
					e.printStackTrace();
					
					onPayResult(false);
				}
			}
		};
		
		Integer mm = Integer.valueOf(money/10);
		GamePropsInfo propsSecond = new GamePropsInfo("1064", mm.toString(), "大司命卡牌","");
		propsSecond.setThirdPay("qpfangshua");
		DKPlatform.getInstance().invokePayCenterActivity(AppActivity.self, propsSecond, 
									null, null, null, null, RechargeCallback);
	}
	
}
