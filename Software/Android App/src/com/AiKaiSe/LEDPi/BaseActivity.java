package com.AiKaiSe.LEDPi;

import android.app.Activity;
import android.content.Intent;
import android.content.pm.PackageManager.NameNotFoundException;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.widget.Toast;

import com.AiKaiSe.Modul.Plasma.PlasmaActivity;
import com.AiKaiSe.Network.Message;
import com.AiKaiSe.Values.FunctionCode;

//This Activity is The Mother of all Activitys wich shoes a
//View for the User or Interaktion
public class BaseActivity extends Activity {
	
	private static final String TAG = BaseActivity.class.getSimpleName();
	
	// If a Item on the Option Menü is selected, handle here.
	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		switch (item.getItemId()) {
		case R.id.settings:
			Log.d(TAG, "Menu Settings selected");
			startActivity(new Intent(this, SettingsActivity.class));
			return true;
		case R.id.handshake:
			Log.d(TAG, "Menu handshake selected");
			try {
				long start = System.currentTimeMillis();
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
				long stop = System.currentTimeMillis() - start;
				Toast.makeText(getApplicationContext(), String.valueOf(stop),
						Toast.LENGTH_SHORT).show();
			} catch (NameNotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			// startActivity(new Intent(this, About.class));
			return true;
		case R.id.test:
			Log.d(TAG, "Menu test selected");
			// Startup hier testen !
			startActivity(new Intent(this, PlasmaActivity.class));
			return true;
		case R.id.versions:
			Log.d(TAG, "Menu about selected");
			startActivity(new Intent(this, ModulVersionsActivity.class));
			return true;
		case R.id.deaktivate:
			// Deaktivate the Current aktive Modul.
			Log.d(TAG, "Menu help selected");
			Message receivemessage = StartActivity.comunicationHandler
					.sendrequest(FunctionCode.GMODULE, new byte[] { 0, 0 });

			if (receivemessage != null && receivemessage.data[0] == 0
					&& receivemessage.data[1] == 0)
				if (this.getClass() != ModulsListActivity.class) {
					this.finish();
					Toast.makeText(getApplicationContext(),
							"Active module disabled", Toast.LENGTH_SHORT)
							.show();
				}
			// startActivity(new Intent(this, Help.class));
			return true;

		default:
			Log.d(TAG, "Menu default catch");
			return super.onOptionsItemSelected(item);
		}
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		MenuInflater inflater = getMenuInflater();
		inflater.inflate(R.menu.settings_menu, menu);
		return true;
	}
	
}
