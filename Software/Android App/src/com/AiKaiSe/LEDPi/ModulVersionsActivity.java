package com.AiKaiSe.LEDPi;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

import android.content.Context;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.util.Log;
import android.widget.ListView;
import android.widget.SimpleAdapter;

//This Activtiy showes the Modul Versions 
public class ModulVersionsActivity extends BaseActivity {
	
	private static final String TAG = ModulVersionsActivity.class.getSimpleName();

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_versions);
		Map<String, ?> listItems = null;

		SharedPreferences saved_values = this.getSharedPreferences(
				"com.LEDpi.ModulVersions", Context.MODE_PRIVATE);
		listItems = saved_values.getAll();

		ArrayList<HashMap<String, String>> data = new ArrayList<HashMap<String, String>>();

		HashMap<String, String> item;

		for (Map.Entry<String, ?> entry : listItems.entrySet()) {
			item = new HashMap<String, String>();
			item.put("line1", entry.getKey());
			item.put("line2", entry.getValue().toString());
			data.add(item); // TODO Versions in List View bekommen
			Log.d(TAG, entry.getKey() + ": "
					+ entry.getValue().toString());
		}

		SimpleAdapter sa;

		sa = new SimpleAdapter(this, data, android.R.layout.two_line_list_item,
				new String[] { "line1", "line2" }, new int[] {
						android.R.id.text1, android.R.id.text2 });

		final ListView listview = (ListView) findViewById(R.id.listView1);
		listview.setAdapter(sa);
	}
}