package com.AiKaiSe.Modul.Mono;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.CheckBox;
import android.widget.LinearLayout;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;

import com.AiKaiSe.LEDPi.BaseActivity;
import com.AiKaiSe.LEDPi.R;

public class MonoActivity extends BaseActivity implements OnClickListener,
		OnSeekBarChangeListener, MonoOnColorChangedListener {

	private static final String TAG = MonoActivity.class.getSimpleName();
	
	private MonoHandler monoHandler;
	private MonoOnColorChangedListener mListener;
	private LinearLayout linearLayout;

	SeekBar seekBarOnTime;
	SeekBar seekBarOffTime;
	CheckBox checkBoxStrobe;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

			setContentView(R.layout.activity_mono);

			seekBarOnTime = (SeekBar) findViewById(R.id.SeekBar1);
			seekBarOnTime.setOnSeekBarChangeListener(this);
			seekBarOffTime = (SeekBar) findViewById(R.id.SeekBar2);
			seekBarOffTime.setOnSeekBarChangeListener(this);

			checkBoxStrobe = (CheckBox) findViewById(R.id.checkBox1);
			checkBoxStrobe.setOnClickListener(this);

			monoHandler = new MonoHandler(checkBoxStrobe, seekBarOnTime,
					seekBarOffTime);

			linearLayout = (LinearLayout) findViewById(R.id.colorPicker);
			linearLayout.addView(CreateView(), 0);
		
	}

	public View CreateView() {
		View v = new MonoColorPickerView(this.getBaseContext(), this, monoHandler,
				this);
		return v;
	}

	@Override
	public void onClick(View v) {
		// If Checbox Checkte or unchecked handle here
		if (v == checkBoxStrobe) {
			monoHandler.send();
		}
	}

	@Override
	public void onProgressChanged(SeekBar seekBar, int progress,
			boolean fromUser) {
		if (fromUser) {

			if (seekBar == seekBarOnTime) {
				Log.d(TAG, "SeekBarOnTime onProgressChange");
				if (checkBoxStrobe.isChecked()) {
					seekBarOffTime.setProgress(seekBarOnTime.getProgress());
					monoHandler.offTime = progress;
					monoHandler.onTime = progress;
					monoHandler.send();
				}
			}
			if (seekBar == seekBarOffTime) {
				Log.d(TAG, "SeekBarOffTime onProgressChange");
				if (checkBoxStrobe.isChecked()) {
					monoHandler.offTime = progress;
					monoHandler.send();
				}
			}
		}
	}

	@Override
	public void onStartTrackingTouch(SeekBar seekBar) {
		// TODO Auto-generated method stub
	}

	@Override
	public void onStopTrackingTouch(SeekBar seekBar) {
		// TODO Auto-generated method stub
	}

	@Override
	public void colorChanged(int color) {
		mListener.colorChanged(color);
	}
}
