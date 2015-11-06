/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.json.JSONObject;

import com.duoku.platform.single.DKPlatform;
import com.duoku.platform.single.DkErrorCode;
import com.duoku.platform.single.DkProtocolKeys;
import com.duoku.platform.single.callback.*;
import com.duoku.platform.single.item.*;
import com.duoku.platform.single.DKPlatformSettings;

import android.os.Bundle;
import android.util.Log;

public class AppActivity extends Cocos2dxActivity {
	
	public static AppActivity self = null; 
			
	protected void onCreate(final Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		self = this;
		initSDK();
	}

	// 初始化SDK
	private void initSDK() {
		// 回调函数
		IDKSDKCallBack initcompletelistener = new IDKSDKCallBack() {
			@Override
			public void onResponse(String paramString) {
				Log.d("GameMainActivity", paramString);
				try {
					JSONObject jsonObject = new JSONObject(paramString);
					// 返回的操作状态码
					int mFunctionCode = jsonObject
							.getInt(DkProtocolKeys.FUNCTION_CODE);

					// 初始化完成
					if (mFunctionCode == DkErrorCode.BDG_CROSSRECOMMEND_INIT_FINSIH) {
						initAds();
					}

				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		};

		// 参数为测试数据，接入时请填入你真实数据
		DKCMMMData mmData = null;

		DKCMGBData gbData = null;

		// 初始化函数
		DKPlatform.getInstance().init(this, true,
				DKPlatformSettings.SdkMode.SDK_PAY, mmData, gbData,
				initcompletelistener);
	}

	private void initAds() {
		DKPlatform.getInstance().bdgameInit(this, new IDKSDKCallBack() {
			@Override
			public void onResponse(String paramString) {
				Log.d("GameMainActivity", "bggameInit success");
			}
		});
	}

	protected void onResume() {
		DKPlatform.getInstance().resumeBaiduMobileStatistic(this);
		super.onResume();
	}

	protected void onPause() {
		DKPlatform.getInstance().pauseBaiduMobileStatistic(this);
		super.onPause();
	}
}
