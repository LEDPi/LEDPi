package com.AiKaiSe.LEDPi;

import java.math.BigInteger;

import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;
import android.content.pm.PackageManager.NameNotFoundException;
import android.preference.PreferenceManager;
import android.util.Log;

import com.AiKaiSe.Network.ComunicationHandler;
import com.AiKaiSe.Network.Message;
import com.AiKaiSe.Values.FunctionCode;
import com.AiKaiSe.Values.Modul;

public class LEDPIHandler extends Activity{
	
	private static final String TAG = ComunicationHandler.class.getSimpleName();
	
	SharedPreferences preferences;
	
	Context myContext;
	
	public LEDPIHandler(Context context){
		myContext = context;
		preferences = PreferenceManager.getDefaultSharedPreferences(myContext);
	}
	
	public boolean handshake() throws NameNotFoundException {
		Log.d(TAG, "handshake called");

		int version = preferences.getInt("versionname", 0);

		byte[] tempbuffer = new byte[3];
		tempbuffer[0] = (byte) ((version & (0xFF << 8)) >>> 8); // High Byte
		tempbuffer[1] = (byte) (version & 0xFF); // Low Byte

		tempbuffer[2] = 0x01; // High Byte

		Message receivemessage = StartActivity.comunicationHandler.sendrequest(FunctionCode.Handshake, tempbuffer);

		if (receivemessage == null) {
			Log.w(TAG, "handshake: receive Message == 0 ");
			return false;
		} else if (receivemessage.fc == FunctionCode.Error.getvalue()) {
			String i = Integer.toHexString((receivemessage.data[3]));
			// TODO Log Errorcode in Name des Errors wandeln.
			Log.w(TAG, "handshake: Error code detected: "
					+ i);
			Log.e(TAG, "Error: " + i);
			return false;
		} else if (receivemessage.data.length < 5) {
			Log.w(TAG, "handshake: lenght < 5");
			return false;
		} else {
			Log.d(TAG,
					"handshake: sucess coding Informations");

			SharedPreferences.Editor editor = preferences.edit();
			editor.putInt("size_x", receivemessage.data[2]);
			editor.putInt("size_y", receivemessage.data[3]);
			editor.putInt("depth", receivemessage.data[4]);
			editor.commit();

			return true;
		}
	}
	
	public byte[] version_info() {
		Log.d(TAG, "version_info: called");
		Message receivemessage = StartActivity.comunicationHandler.sendrequest(FunctionCode.VersionInfo, null);

		if (receivemessage == null) {
			Log.w(TAG,
					"version_info: Receive Message == null");
			return null;
		} else if (receivemessage.fc == FunctionCode.Error.getvalue()) {
			String i = Integer.toHexString((receivemessage.data[3]));
			Log.w(TAG, "version_info: detectes Error: " + i);
			Log.e(TAG, "Error: " + i);

			return null;
		} else {
			Log.d(TAG, "version_info: Receive Informations");
			byte[] moduls;
			moduls = new byte[receivemessage.data.length];
			System.arraycopy(receivemessage.data, 0, moduls, 0, moduls.length);

			Log.e(TAG, "Version Info sucess");

			return moduls;
		}
	}
	
	// data Array Modul wahl um ein Modul auszuwählen ansonsten null übergeben
	// !!
	public int gModul(Modul modul) {
		Log.d(TAG, "gModul: called");
		Message receivemessage;

		if (modul == null) {
			Log.w(TAG,
					"gModul: Modul = null --> get Active Moduls ");
			receivemessage = StartActivity.comunicationHandler.sendrequest(FunctionCode.GMODULE, null);
		} else {
			Log.d(TAG,
					"gModul: Activate Modul " + modul.getvalue());
			byte[] data = new byte[2];
			data[0] = (byte) ((modul.getvalue() & (0xFF << 8)) >>> 8);
			data[1] = (byte) (modul.getvalue() & 0xFF);

			receivemessage = StartActivity.comunicationHandler.sendrequest(FunctionCode.GMODULE, data);
		}

		int am = 0;
		if (receivemessage == null) {
			Log.w(TAG, "gModul: receive Message == null");
			return am;

		} else if (receivemessage.fc == FunctionCode.Error.getvalue()) {
			String i = Integer.toHexString((receivemessage.data[3]));

			Log.w(TAG, "gModul: Error detected: " + i);
			Log.e(TAG, "Error: " + i);

			return 0;
		} else {
			Log.d(TAG,
					"gModul: received Modul Informations ");
			byte[] activeModul;
			activeModul = new byte[receivemessage.data.length];
			System.arraycopy(receivemessage.data, 0, activeModul, 0,
					activeModul.length);

			Log.d(TAG, "Version Info sucess");

			if (activeModul.length == 2) {
				BigInteger bi = new BigInteger(1, activeModul);
				String hexstring = String.format("%0"
						+ (activeModul.length << 1) + "X", bi);

				am = Integer.parseInt(hexstring, 16);

				if (am == 0) {
					Log.d(TAG,
							"gModul: No modul active -> u can activate some Modul");
					Log.w(TAG, "No modul active");
				} else {
					Log.d(TAG,
							"gModul: Modul " + Modul.getName(am) + " active");
				}

			} else {
				Log.w(TAG,
						"gModul: Error in Modul code. Code is < > as 2");
			}

			return am;
		}

	}
	
	public static int hexToInt(byte[] twobytes) {
		BigInteger bi = new BigInteger(1, twobytes);
		String hexstring = String.format("%0" + (twobytes.length << 1) + "X",
				bi);
		return Integer.parseInt(hexstring, 16);
	}

}
