package com.AiKaiSe.Modul.Photo;

import java.util.HashMap;

import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.ListView;

import com.AiKaiSe.LEDPi.BaseActivity;
import com.AiKaiSe.LEDPi.R;

public class PhotoActivity extends BaseActivity implements
		OnItemClickListener {

	private static final String TAG = PhotoActivity.class.getSimpleName();

	ListView listview;
	PhotoHandler photoHandler;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		Log.d(TAG, "On Create");

			// If Modul loadet go on ...
			Log.d(TAG, "Modul loaded");

			setContentView(R.layout.activity_photo);

			listview = (ListView) findViewById(R.id.maplist_photo);
			photoHandler = new PhotoHandler();

			StableArrayAdapter adapter = new StableArrayAdapter(this,
					R.layout.main_list_item);
			listview.setAdapter(adapter);
			listview.setOnItemClickListener(this);
		
	}

	@Override
	public void onItemClick(AdapterView<?> listView, View view, int position,
			long id) {
		Log.d(TAG, "Click Item");
		photoHandler.send(id);

	}

	private class StableArrayAdapter extends ArrayAdapter<String> {
		HashMap<String, Integer> mIdMap = new HashMap<String, Integer>();

		public StableArrayAdapter(Context context, int textViewResourceId) {
			super(context, textViewResourceId);

			for (Photo p : Photo.values()) {
				mIdMap.put(p.name(), p.getvalue());
				this.add(p.name());
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
}
