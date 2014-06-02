package com.AiKaiSe.LEDPi;

import java.util.regex.Pattern;

import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.OnSharedPreferenceChangeListener;
import android.content.pm.PackageManager.NameNotFoundException;
import android.content.res.Resources.NotFoundException;
import android.os.Bundle;
import android.preference.PreferenceActivity;
import android.preference.PreferenceManager;
import android.util.Log;
import android.widget.Toast;

public class SettingsActivity extends PreferenceActivity implements
		OnSharedPreferenceChangeListener {
	
	private static final String TAG = SettingsActivity.class.getSimpleName();

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		Log.d(TAG, "onCreate called");

		addPreferencesFromResource(R.xml.settings);
		
		

		SharedPreferences preferences = PreferenceManager
				.getDefaultSharedPreferences(this);
		preferences.registerOnSharedPreferenceChangeListener(this);
	}

	final Pattern IP_ADDRESS = Pattern
			.compile("((25[0-5]|2[0-4][0-9]|[0-1][0-9]{2}|[1-9][0-9]|[1-9])\\.(25[0-5]|2[0-4]"
					+ "[0-9]|[0-1][0-9]{2}|[1-9][0-9]|[1-9]|0)\\.(25[0-5]|2[0-4][0-9]|[0-1]"
					+ "[0-9]{2}|[1-9][0-9]|[1-9]|0)\\.(25[0-5]|2[0-4][0-9]|[0-1][0-9]{2}"
					+ "|[1-9][0-9]|[0-9]))");

	@Override
	public void onSharedPreferenceChanged(SharedPreferences sharedPreferences,
			String key) {
		Log.d(TAG, "onSharedPreferenceChanged: ");

		if (key.equals("raspiAdress")) {
			SharedPreferences.Editor myEditor = sharedPreferences.edit();

			String whatWasTyped = sharedPreferences.getString("raspiAdress",
					"n/a");
			CharSequence s = whatWasTyped;
			if (IP_ADDRESS.matcher(s).matches()) {
				String previousText = s.toString();
				myEditor.putString(key, previousText);
			} else {
				myEditor.putString("raspiAdress", "192.168.1.12");
				Toast.makeText(this, "Wrong IP Format !", Toast.LENGTH_SHORT)
						.show();
				Toast.makeText(this, "IP set to default", Toast.LENGTH_SHORT)
						.show();
			}
			try {
				if (!StartActivity.ledPIHandler.handshake()) {
					Toast.makeText(getApplicationContext(),
							R.string.error_handshake, Toast.LENGTH_SHORT)
							.show();

				} else {
					Toast.makeText(getApplicationContext(),
							R.string.sucess_handshake, Toast.LENGTH_SHORT)
							.show();
					startActivity(new Intent(this, ModulsListActivity.class));
					finish();
				}
			} catch (NameNotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (NotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			myEditor.commit();
		}
		
		if (key.equals("raspiPort")) {
			try {
				if (!StartActivity.ledPIHandler.handshake()) {
					Toast.makeText(getApplicationContext(),
							R.string.error_handshake, Toast.LENGTH_SHORT)
							.show();

				} else {
					Toast.makeText(getApplicationContext(),
							R.string.sucess_handshake, Toast.LENGTH_SHORT)
							.show();
					startActivity(new Intent(this, ModulsListActivity.class));
					finish();
				}
			} catch (NameNotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (NotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

		setPreferenceScreen(null);
		addPreferencesFromResource(R.xml.settings);
	}

}
