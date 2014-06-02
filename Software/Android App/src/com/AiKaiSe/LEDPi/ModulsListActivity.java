package com.AiKaiSe.LEDPi;

import java.math.BigInteger;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.PackageManager.NameNotFoundException;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.Toast;

import com.AiKaiSe.Network.Message;
import com.AiKaiSe.Values.FunctionCode;
import com.AiKaiSe.Values.Modul;

//This is the Main Activity. With a List you can start the Available Moduls
public class ModulsListActivity extends BaseActivity implements
		OnItemClickListener {
	
	private static final String TAG = ModulsListActivity.class.getSimpleName();

	private byte[] moduls = null;
	ListView listview;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		Log.d(TAG, "onCreate called");

		setContentView(R.layout.activity_main);
		
		SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(this);
		setTitle("LEDPI - " + preferences.getString("versionName", "n/a"));
		
		listview = (ListView) findViewById(R.id.mylist);

		// ////////////////////////////////////////////////////////////////////////////
		// StartUp
		// ///////////////////////////////////////////////////////////////////////////

		// ////////////////Handshake////////////////
		try {
			WifiManager wifiManager = (WifiManager) this.getSystemService(this.WIFI_SERVICE);
			
			if (!StartActivity.ledPIHandler.handshake()) {

				startActivity(new Intent(this, NoConnectionActivity.class));
				Log.w(TAG, "handshake dismiss");
				Log.d(TAG, "Activity NoConnection create !");
				Toast.makeText(this, "Handshake fehlgeschlagen !!",
						Toast.LENGTH_SHORT).show();
				if(!wifiManager.isWifiEnabled()){
					Toast.makeText(this, "W-Lan nicht eingeschaltet !!",
							Toast.LENGTH_LONG).show();
					
					startActivity(new Intent(WifiManager.ACTION_PICK_WIFI_NETWORK));
					
				}
				
				this.finish();
			} else {
				Toast.makeText(getApplicationContext(),
						"Handshake erfolgreich !!", Toast.LENGTH_SHORT).show();
				Log.d(TAG, "handshake sucess");

				// ////////////Version Info/////////////
				byte[] temp = StartActivity.ledPIHandler.version_info();

				if (temp == null && temp.length % 4 == 0) {
					Log.d(TAG,
							"version_info: no Moduls from Pi dismiss");
					Toast.makeText(getApplicationContext(),
							"Keine Module vorhanden", Toast.LENGTH_SHORT)
							.show();
				} else {
					Log.d(TAG,
							"version_info: get Moduls from Pi ");
					Toast.makeText(getApplicationContext(), "Module vorhanden",
							Toast.LENGTH_SHORT).show();

					String[] tempstr = new String[temp.length / 4];
					moduls = new byte[temp.length / 2];

					if (temp.length / 4 != 0) {
						Log.d(TAG, "version_info: convert Moduls:");

						SharedPreferences saved_values = this
								.getSharedPreferences(
										"com.LEDpi.ModulVersions", 0);

						SharedPreferences.Editor modulversions = saved_values
								.edit();
						modulversions.clear();

						for (int i = 0; i < temp.length; i = i + 4) {

							byte[] modul = new byte[2];
							System.arraycopy(temp, i, moduls, i / 2, 2);

							// Modul Name
							System.arraycopy(temp, i, modul, 0, 2);
							BigInteger bi = new BigInteger(1, modul);
							String hexstring = String.format("%0"
									+ (modul.length << 1) + "X", bi);
							tempstr[i / 4] = Modul.getName(Integer.parseInt(
									hexstring, 16));

							Log.d(TAG, "version_info: Modul "
									+ hexstring + " detected ");

							// Modul Version
							byte[] modulversion = new byte[2];
							System.arraycopy(temp, i + 2, modulversion, 0, 2);
							BigInteger bi2 = new BigInteger(1, modulversion);
							String hexstringversion = String.format("%0"
									+ (modulversion.length << 1) + "X", bi2);

							modulversions.putString(
									Modul.getName(bi.intValue()),
									hexstringversion);
						}
						modulversions.commit();
					}

					// Check for active Modul
					Message receivemessage = StartActivity.comunicationHandler
							.sendrequest(FunctionCode.GMODULE, null);
					if (receivemessage.data.length == 2) {
						int activeModul = LEDPIHandler.hexToInt(new byte[] {
								receivemessage.data[0], receivemessage.data[1] });
						if (Modul.getActivity(activeModul) != null)
							startActivity(new Intent(ModulsListActivity.this,
									Modul.getActivity(activeModul)));
					}
				}

				// ///////////////Startup  End///////////////////////////

				// create List View with values = ListItems
				final ArrayList<Integer> list = new ArrayList<Integer>();
				for (int i = 0; i < moduls.length; i = i + 2) {				
					
					byte[] t = {moduls[i],moduls[i + 1]};
					int mid = LEDPIHandler.hexToInt(t);
					
					Log.d(TAG, "Modul hast UI ?");
					Log.d(TAG, "Modul id: " + mid + " (" + Modul.hasUserInterface(mid) + ")");
					if(Modul.hasUserInterface(mid)){
						list.add(mid);
						Log.d(TAG, "add :" + mid + " to Modul List with UI");
					}
				}

				// create Standart StableArrayAdapter for Handel List Items
				final StableArrayAdapter adapter = new StableArrayAdapter(this,
						R.layout.main_list_item, list);
				listview.setAdapter(adapter);
				listview.setOnItemClickListener(this);

			}
			
			
			
			
			
		} catch (NumberFormatException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (NameNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	
	private void activateModul(Modul modul) {
		boolean active = false;

		//If Modul is aktive
		if (StartActivity.ledPIHandler.gModul(null) == modul.getvalue()) {
			active = true;
		}
		
		//Check for Modul was loaded ...
		if (!active
				&& StartActivity.ledPIHandler.gModul(modul) != modul
						.getvalue()) {
			Log.d(TAG, "Module could not be loaded !");
			Toast.makeText(this, "Modul nicht geladen!", Toast.LENGTH_SHORT)
					.show();

		} else {
			// If Modul loadet go on ...
			Log.d(TAG, "Activate Modul: " + modul.getvalue());
			Toast.makeText(this, "Modul geladen!", Toast.LENGTH_SHORT).show();

			if (Modul.getActivity(modul.getvalue()) != null) {
				startActivity(new Intent(this, Modul.getActivity(modul
						.getvalue())));
			}
		}
	}

	//Array Adapter for the List View with the Moduls
	private class StableArrayAdapter extends ArrayAdapter<String> {
		HashMap<String, Integer> mIdMap = new HashMap<String, Integer>();

		public StableArrayAdapter(Context context, int textViewResourceId,
				List<Integer> ids) {
			super(context, textViewResourceId);

			for (int i = 0; i < ids.size(); ++i) {
				mIdMap.put(Modul.getName(ids.get(i)), ids.get(i));
				this.add(Modul.getName(ids.get(i)));
			}
		}

		@Override
		public long getItemId(int position) {
			String item = getItem(position);
			return mIdMap.get(item);
		}

		@Override
		public boolean hasStableIds() {
			return true;
		}
	}

	@Override
	public void onItemClick(AdapterView<?> listView, View view, int position,
			long id) {
		if (listView == listview) {
			
			Log.d(TAG, "on Item click listener: onClick");
			activateModul(Modul.getById(id));
		}
	}
}
