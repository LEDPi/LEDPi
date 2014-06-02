package com.AiKaiSe.Modul.Photo;

import android.app.Activity;
import android.util.Log;

import com.AiKaiSe.LEDPi.StartActivity;
import com.AiKaiSe.Values.FunctionCode;

public class PhotoHandler extends Activity {

	private static final String TAG = PhotoHandler.class.getSimpleName();


	public void send(long id) {
		Log.d(TAG, "sendPhoto: " + id);
		
		byte[] data = new byte[2];
		data[0] = (byte) ((id & (0xFF << 8)) >>> 8);
		data[1] = (byte) (id & 0xFF);
		
		StartActivity.comunicationHandler.send(FunctionCode.PHOTO_CHANGE, data);
	
	}

}
