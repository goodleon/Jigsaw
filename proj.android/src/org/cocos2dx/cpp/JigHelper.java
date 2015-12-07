package org.cocos2dx.cpp;

import org.json.JSONObject;

import android.content.pm.ApplicationInfo;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.util.Log;
import android.widget.Toast;

public class JigHelper {
	public static String get_version(){
		try{
			PackageManager mgr = AppActivity.self.getPackageManager();
			PackageInfo packageInfo = mgr.getPackageInfo("com.zz.Jigsaw", 0);
	        return packageInfo.versionName;	
		}catch(Exception e){
			Log.e("jigsaw.error", e.getMessage());
			return "0.0";
		}
	}
}
