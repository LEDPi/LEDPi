package com.AiKaiSe.Modul.Plasma;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.widget.Spinner;

import com.AiKaiSe.LEDPi.BaseActivity;
import com.AiKaiSe.LEDPi.R;

public class PlasmaActivity extends BaseActivity implements
		OnSeekBarChangeListener, OnClickListener, OnItemSelectedListener {

	private static final String TAG = PlasmaActivity.class.getSimpleName();

	private final float CONCENTRICSCALE_MAX = 2500;
	private final float CONCENTRICSCALE_MIN = 1;
	private final double CONCENTRICSCALE_MAX_CALC = Integer.MAX_VALUE/(CONCENTRICSCALE_MAX-CONCENTRICSCALE_MIN);
	
	private final float CONCENTRICSPEED_MAX = 5;
	private final float CONCENTRICSPEED_MIN = 1;
	private final double CONCENTRICSPEED_MAX_CALC = Integer.MAX_VALUE/(CONCENTRICSPEED_MAX-CONCENTRICSPEED_MIN);
	
	private final float PERIOD_MAX = 2;
	private final double PERIOD_MAX_CALC = Integer.MAX_VALUE/PERIOD_MAX;
	
	private final float SPEED_MAX = 1;
	private final double SPEED_MAX_CALC = Integer.MAX_VALUE/SPEED_MAX;
	
	private PlasmaHandler plasmaHandler;

	private Spinner spinnerMethod;
	private Spinner spinnerColor;

	private SeekBar seekBarConcentricScale;
	private SeekBar seekBarConcentricSpeed;
	private SeekBar seekBarPeriod;
	private SeekBar seekBarSpeed;

	private CheckBox checkBoxInvert;
	
	private Button buttonStandard;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_plasma);

		plasmaHandler = new PlasmaHandler();

		spinnerMethod = (Spinner) findViewById(R.id.spinner_method);
		spinnerMethod.setOnItemSelectedListener(this);
		
		spinnerColor = (Spinner) findViewById(R.id.spinner_color);
		spinnerColor.setOnItemSelectedListener(this);

		seekBarConcentricScale = (SeekBar) findViewById(R.id.SeekBar_ConcentricScale);
		seekBarConcentricScale.setOnSeekBarChangeListener(this);
		seekBarConcentricScale.setMax(Integer.MAX_VALUE);
		
		seekBarConcentricSpeed = (SeekBar) findViewById(R.id.SeekBar_ConcentricSpeed);
		seekBarConcentricSpeed.setOnSeekBarChangeListener(this);
		seekBarConcentricSpeed.setMax(Integer.MAX_VALUE);
		
		seekBarPeriod = (SeekBar) findViewById(R.id.SeekBar_Period);
		seekBarPeriod.setOnSeekBarChangeListener(this);
		seekBarPeriod.setMax(Integer.MAX_VALUE);
		
		seekBarSpeed = (SeekBar) findViewById(R.id.SeekBar_Speed);
		seekBarSpeed.setOnSeekBarChangeListener(this);
		seekBarSpeed.setMax(Integer.MAX_VALUE);

		checkBoxInvert = (CheckBox) findViewById(R.id.checkBoxInvert);
		checkBoxInvert.setOnClickListener(this);
		
		buttonStandard = (Button) findViewById(R.id.buttonStandard);
		buttonStandard.setOnClickListener(this);
		
		initUI();

		
	}
	
	public void initUI(){
		
		spinnerColor.setSelection(plasmaHandler.getColor().getValue());

		spinnerMethod.setSelection(plasmaHandler.getMethod().getValue());

		seekBarConcentricScale.setProgress( (int) (plasmaHandler.getConcentricScale() * CONCENTRICSCALE_MAX_CALC));
		
		seekBarConcentricSpeed.setProgress( (int) (plasmaHandler.getConcentricSpeed() * CONCENTRICSPEED_MAX_CALC));
		
		seekBarPeriod.setProgress( (int) (plasmaHandler.getPeriod() * PERIOD_MAX_CALC));
		
		seekBarSpeed.setProgress( (int) (plasmaHandler.getSpeed() * SPEED_MAX_CALC));

		checkBoxInvert.setChecked(plasmaHandler.isInvert());
		
	}

	@Override
	public void onProgressChanged(SeekBar seekBar, int progress,
			boolean fromUser) {
		if (fromUser) {

			if (seekBar == seekBarConcentricScale) {
				plasmaHandler.setConcentricScale((float)  (seekBar.getProgress()/(CONCENTRICSCALE_MAX_CALC+CONCENTRICSCALE_MIN)));
			}
			if (seekBar == seekBarConcentricSpeed) {
				plasmaHandler.setConcentricSpeed((float)  (seekBar.getProgress()/(CONCENTRICSPEED_MAX_CALC+CONCENTRICSPEED_MIN)));
			}
			if (seekBar == seekBarPeriod) {
				plasmaHandler.setPeriod((float) (seekBar.getProgress()/PERIOD_MAX_CALC));
			}
			if (seekBar == seekBarSpeed) {
				plasmaHandler.setSpeed((float) (seekBar.getProgress()/SPEED_MAX_CALC));
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
	public void onClick(View v) {

		if (v == checkBoxInvert) {
			plasmaHandler.setInvert(checkBoxInvert.isChecked());
		}
		if (v == buttonStandard){
			plasmaHandler = new PlasmaHandler();
			plasmaHandler.send();
			initUI();
		}

	}

	@Override
	public void onItemSelected(AdapterView<?> parent, View view, int pos,
			long id) {
		Log.e(TAG, "id: " + id + " pos: " + pos);
		if (parent == spinnerColor) {
			plasmaHandler.setColor(Color.getById(pos));
		}
		if (parent == spinnerMethod) {
			plasmaHandler.setMethod(Method.getById(pos));
		}
	}

	@Override
	public void onNothingSelected(AdapterView<?> arg0) {
		// TODO Auto-generated method stub

	}

}
