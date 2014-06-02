package com.AiKaiSe.LEDPi;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.PackageManager.NameNotFoundException;
import android.os.Bundle;
import android.os.Handler;
import android.preference.PreferenceManager;
import android.util.Log;

import com.AiKaiSe.Network.ComunicationHandler;

//This is the Activity with the LEDPI Logo
public class StartActivity extends Activity {
	
	private static final String TAG = StartActivity.class.getSimpleName();

	public static ComunicationHandler comunicationHandler;
	public static LEDPIHandler ledPIHandler;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		ledPIHandler = new LEDPIHandler(this);
		
		Log.d(TAG, "onCreate called");
		comunicationHandler = new ComunicationHandler(getApplicationContext());

		try {
			SharedPreferences preferences = PreferenceManager
					.getDefaultSharedPreferences(this);

			PreferenceManager.setDefaultValues(this, R.xml.settings, false);

			SharedPreferences.Editor editor = preferences.edit();
			editor.putString("versionName", String.valueOf(getPackageManager()
					.getPackageInfo(getPackageName(), 0).versionName));
			editor.putString(
					"versionCode",
					getPackageManager().getPackageInfo(getPackageName(), 0).versionName);
			editor.commit();
			Log.d(TAG,
					"Edit Preferences with new Version and Versioncode from App");

		} catch (NameNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		setContentView(R.layout.activity_start);

		new Handler().postDelayed(new Runnable() {
			@Override
			public void run() {

				startActivity(new Intent(StartActivity.this,
						ModulsListActivity.class));
				Log.d(TAG, "Start new Intent MainActivity");
				finish();
			}
		}, 1000);
	}
}