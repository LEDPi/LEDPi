package com.AiKaiSe.Modul.Snake;

import android.app.Activity;
import android.util.Log;

import com.AiKaiSe.LEDPi.StartActivity;
import com.AiKaiSe.Values.FunctionCode;

public class SnakeHandler extends Activity {

	private static final String TAG = SnakeHandler.class.getSimpleName();

	public void sendMap(long id) {
		Log.d(TAG, "sendMap with id : " + id);
		byte[] data = new byte[1];
		data[0] = (byte) id;

		StartActivity.comunicationHandler.send(FunctionCode.SNAKE_START, data);
	}

	public void sendUp() {
			Log.d(TAG, "sendUp");
			byte[] data = new byte[1];
			data[0] = (byte) SnakeDirection.UP.getvalue();
			StartActivity.comunicationHandler.send(
					FunctionCode.SNAKE_DIRECTION, data);
	}

	public void sendDown() {
			Log.d(TAG, "sendDown");
			byte[] data = new byte[1];
			data[0] = (byte) SnakeDirection.DOWN.getvalue();
			StartActivity.comunicationHandler.send(
					FunctionCode.SNAKE_DIRECTION, data);
	}

	public void sendLeft() {
			Log.d(TAG, "sendLeft");
			byte[] data = new byte[1];
			data[0] = (byte) SnakeDirection.LEFT.getvalue();
			StartActivity.comunicationHandler.send(
					FunctionCode.SNAKE_DIRECTION, data);
	}

	public void sendRight() {
			Log.d(TAG, "sendRight");
			byte[] data = new byte[1];
			data[0] = (byte) SnakeDirection.RIGHT.getvalue();
			StartActivity.comunicationHandler.send(
					FunctionCode.SNAKE_DIRECTION, data);
	}
}
