package com.AiKaiSe.Modul.Snake;

import java.util.HashMap;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.ListView;

import com.AiKaiSe.LEDPi.BaseActivity;
import com.AiKaiSe.LEDPi.R;

public class SnakeMapActivity extends BaseActivity implements
		OnItemClickListener {

	private static final String TAG = SnakeMapActivity.class.getSimpleName();

	ListView listview;
	SnakeHandler snakeHandler;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

			setContentView(R.layout.activity_snake_map);

			listview = (ListView) findViewById(R.id.maplist_snake);
			snakeHandler = new SnakeHandler();

			StableArrayAdapter adapter = new StableArrayAdapter(this,
					R.layout.main_list_item);
			listview.setAdapter(adapter);
			listview.setOnItemClickListener(this);

		
	}

	@Override
	public void onItemClick(AdapterView<?> listView, View view, int position,
			long id) {
		Log.d(TAG, "Click Item ");
		snakeHandler.sendMap(id);
		Intent newIntent = new Intent(SnakeMapActivity.this, SnakeActivity.class);
		this.finish();
		startActivity(newIntent);

	}

	private class StableArrayAdapter extends ArrayAdapter<String> {
		HashMap<String, Integer> mIdMap = new HashMap<String, Integer>();

		public StableArrayAdapter(Context context, int textViewResourceId) {
			super(context, textViewResourceId);

			for (SnakeMap sm : SnakeMap.values()) {
				mIdMap.put(sm.name(), sm.getvalue());
				this.add(sm.name());
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
