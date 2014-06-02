package com.AiKaiSe.Modul.Gradient;

import java.io.IOException;
import java.math.BigInteger;

import android.app.Activity;
import android.util.Log;
import android.widget.CheckBox;
import android.widget.SeekBar;

import com.AiKaiSe.LEDPi.StartActivity;
import com.AiKaiSe.Network.Message;
import com.AiKaiSe.Values.FunctionCode;

public class GradientHandler extends Activity {
	
	private static final String TAG = GradientHandler.class.getSimpleName();

	int[] rgb = new int[3];
	int onTime = 0;
	int offTime = 0;

	private CheckBox blinkCheckBox;
	private SeekBar seekBar1;
	private SeekBar seekBar2;

	public GradientHandler(CheckBox cb, SeekBar sb1, SeekBar sb2) {
		blinkCheckBox = cb;
		seekBar1 = sb1;
		seekBar2 = sb2;

		init();
	}

	private void init() {

		Message receivemessage = StartActivity.comunicationHandler.sendrequest(
				FunctionCode.MONO_MONO, null);
		if (receivemessage != null) {
			if (receivemessage.data != null) {
				rgb[0] = receivemessage.data[0];
				rgb[1] = receivemessage.data[1];
				rgb[2] = receivemessage.data[2];

				if (receivemessage.data[3] != 0 || receivemessage.data[4] != 0
						|| receivemessage.data[5] != 0
						|| receivemessage.data[6] != 0) {

					blinkCheckBox.setChecked(true);
					onTime = hexToInt(new byte[] { receivemessage.data[3],
							receivemessage.data[4] });
					offTime = hexToInt(new byte[] { receivemessage.data[5],
							receivemessage.data[6] });
					seekBar1.setProgress(onTime);
					seekBar2.setProgress(offTime);
				}
			} else {
				Log.w("MonoHandler", "request: receivemessage.data == null !!!");
			}
		} else {
			Log.w("MonoHandler---", "request: receivemessage == null !!!");
		}
	}

	private int hexToInt(byte[] twobytes) {
		BigInteger bi = new BigInteger(1, twobytes);
		String hexstring = String.format("%0" + (twobytes.length << 1) + "X",
				bi);
		return Integer.parseInt(hexstring, 16);
	}

	public void setRGB(int[] inrgb) {
		Log.d(TAG, "set RGB value: Red: " + inrgb[0] + " Green: "
				+ inrgb[1] + " Blue: " + inrgb[2]);
		rgb = inrgb;
	}

	public void send() {
		Log.d(TAG, "sendData: Mono Data send");

		byte[] data = new byte[7];
		data[0] = (byte) rgb[0];
		data[1] = (byte) rgb[1];
		data[2] = (byte) rgb[2];

		if (blinkCheckBox.isChecked()) {
			data[3] = (byte) ((onTime & (0xFF << 8)) >>> 8);
			data[4] = (byte) (onTime & 0xFF);
			data[5] = (byte) ((offTime & (0xFF << 8)) >>> 8);
			data[6] = (byte) (offTime & 0xFF);
		} else {
			data[3] = 0;
			data[4] = 0;
			data[5] = 0;
			data[6] = 0;
		}

		Log.d(TAG, "send: ");

		try {
			StartActivity.comunicationHandler.sendFrequency(
					FunctionCode.MONO_MONO, data);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
