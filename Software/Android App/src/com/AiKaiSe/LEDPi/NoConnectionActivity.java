package com.AiKaiSe.LEDPi;

import android.os.Bundle;
import android.util.Log;

//Activity showen wen there is no Connection to the PI
public class NoConnectionActivity extends BaseActivity {
	
	private static final String TAG = NoConnectionActivity.class.getSimpleName();

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		Log.d(TAG, "onCreate called");
		setContentView(R.layout.activity_no_connection);
		setTitle(R.string.title_activity_no_connection);
	}
}