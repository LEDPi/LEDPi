package com.AiKaiSe.Modul.Ball;

import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;

import com.AiKaiSe.LEDPi.BaseActivity;
import com.AiKaiSe.LEDPi.R;

public class BallActivity extends BaseActivity implements OnSeekBarChangeListener,
		OnClickListener {

	private static final String TAG = BallActivity.class.getSimpleName();

	private final int BALLS_MAX = 10;
	
	private final int SPEED_MAX = 2;
	private final double SPEED_MAX_CALC = Integer.MAX_VALUE/SPEED_MAX;
	
	private final int RED_MAX = 1;
	private final double RED_MAX_CALC = Integer.MAX_VALUE/RED_MAX;
	
	private final int GREEN_MAX = 1;
	private final double GREEN_MAX_CALC = Integer.MAX_VALUE/GREEN_MAX;
	
	private final int BLUE_MAX = 1;
	private final double BLUE_MAX_CALC = Integer.MAX_VALUE/BLUE_MAX;
	
	private final int SIZE_MAX = 10;
	private final double SIZE_MAX_CALC = Integer.MAX_VALUE/SIZE_MAX;
	
	private final int GLOW_MAX = 2;
	private final double GLOW_MAX_CALC = Integer.MAX_VALUE/GLOW_MAX;
	
	private final int RANDOMSPEED_MAX = 10;
	private final double RANDOMSPEED_MIN = 1;
	private final double RANDOMSPEED_MAX_CALC = Integer.MAX_VALUE/(RANDOMSPEED_MAX-RANDOMSPEED_MIN);
	
	
	private BallHandler ballHandler;

	private SeekBar seekBarBalls;
	private SeekBar seekBarSpeed;
	private SeekBar seekBarRed;
	private SeekBar seekBarGreen;
	private SeekBar seekBarBlue;
	private SeekBar seekBarSize;
	private SeekBar seekBarGlow;
	private SeekBar seekBarRandomSpeed;

	private CheckBox checkBoxInvert;
	private CheckBox checkBoxRandom;
	
	private Button buttonStandard;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_ball);

		ballHandler = new BallHandler();

		seekBarBalls = (SeekBar) findViewById(R.id.SeekBar_BallCount);
		seekBarBalls.setOnSeekBarChangeListener(this);
		seekBarBalls.setMax(BALLS_MAX-1);
	
		
		seekBarSpeed = (SeekBar) findViewById(R.id.SeekBar_Speed);
		seekBarSpeed.setOnSeekBarChangeListener(this);
		seekBarSpeed.setMax(Integer.MAX_VALUE);
		
		
		seekBarRed = (SeekBar) findViewById(R.id.SeekBar_Red);
		seekBarRed.setOnSeekBarChangeListener(this);
		seekBarRed.setMax(Integer.MAX_VALUE);
	
		
		seekBarGreen = (SeekBar) findViewById(R.id.SeekBar_Green);
		seekBarGreen.setOnSeekBarChangeListener(this);
		seekBarGreen.setMax(Integer.MAX_VALUE);
		
		
		seekBarBlue = (SeekBar) findViewById(R.id.SeekBar_Blue);
		seekBarBlue.setOnSeekBarChangeListener(this);
		seekBarBlue.setMax(Integer.MAX_VALUE);
	
		
		seekBarSize = (SeekBar) findViewById(R.id.SeekBar_Size);
		seekBarSize.setOnSeekBarChangeListener(this);
		seekBarSize.setMax(Integer.MAX_VALUE);
		
		
		seekBarGlow = (SeekBar) findViewById(R.id.SeekBar_Glow);
		seekBarGlow.setOnSeekBarChangeListener(this);
		seekBarGlow.setMax(Integer.MAX_VALUE);
		
		
		seekBarRandomSpeed = (SeekBar) findViewById(R.id.SeekBar_RandomSpeed);
		seekBarRandomSpeed.setOnSeekBarChangeListener(this);
		seekBarRandomSpeed.setMax(Integer.MAX_VALUE);
		
		
		checkBoxInvert = (CheckBox) findViewById(R.id.checkBoxInvert);
		checkBoxInvert.setOnClickListener(this);
		
		
		checkBoxRandom = (CheckBox) findViewById(R.id.checkBoxRandom);
		checkBoxRandom.setOnClickListener(this);
		
		
		buttonStandard = (Button) findViewById(R.id.buttonStandard);
		buttonStandard.setOnClickListener(this);
		
		ballHandler.receiveState();
		
		initUI();

	}
	
	public void initUI(){

		seekBarBalls.setProgress(ballHandler.getBall());
		
		seekBarSpeed.setProgress( (int) (ballHandler.getSpeed() * SPEED_MAX_CALC));
		
		seekBarRed.setProgress( (int) (ballHandler.getRed() * RED_MAX_CALC));
		
		seekBarGreen.setProgress( (int) (ballHandler.getGreen() * GREEN_MAX_CALC));
		
		seekBarBlue.setProgress( (int) (ballHandler.getBlue() * BLUE_MAX_CALC));
		
		seekBarSize.setProgress( (int) (ballHandler.getSize() * SIZE_MAX_CALC));

		seekBarGlow.setProgress( (int) (ballHandler.getGlow() * GLOW_MAX_CALC));	

		seekBarRandomSpeed.setProgress( (int) (ballHandler.getRandomSpeed() * RANDOMSPEED_MAX_CALC));

		checkBoxInvert.setChecked(ballHandler.isInvert());

		checkBoxRandom.setChecked(ballHandler.isRandom());

		buttonStandard.setOnClickListener(this);
	}

	@Override
	public void onProgressChanged(SeekBar seekBar, int progress,
			boolean fromUser) {
		if (fromUser) {

			if (seekBar == seekBarBalls) {
				ballHandler.setBall(seekBar.getProgress()+1);
			}
			if (seekBar == seekBarSpeed) {
				ballHandler.setSpeed((float)  (seekBar.getProgress()/SPEED_MAX_CALC));
			}
			if (seekBar == seekBarRed) {
				ballHandler.setRed((float) (seekBar.getProgress()/RED_MAX_CALC)); 
			}
			if (seekBar == seekBarGreen) {
				ballHandler.setGreen((float) (seekBar.getProgress()/GREEN_MAX_CALC)); 	
			}
			if (seekBar == seekBarBlue) {
				ballHandler.setBlue((float) (seekBar.getProgress()/BLUE_MAX_CALC)); 
			}
			if (seekBar == seekBarSize) {
				ballHandler.setSize((float) (seekBar.getProgress()/SIZE_MAX_CALC)); 
			}
			if (seekBar == seekBarGlow) {
				ballHandler.setGlow((float) (seekBar.getProgress()/GLOW_MAX_CALC));
			}
			if (seekBar == seekBarRandomSpeed) {
				ballHandler.setRandomSpeed((float)  (seekBar.getProgress()/RANDOMSPEED_MAX_CALC+RANDOMSPEED_MIN));
			}
		}
	}

	@Override
	public void onClick(View v) {

		if (v == checkBoxInvert) {
			ballHandler.setInvert(checkBoxInvert.isChecked());
		}
		if (v == checkBoxRandom) {
			ballHandler.setRandom(checkBoxRandom.isChecked());
		}
		if (v == buttonStandard){
			ballHandler = new BallHandler();
			ballHandler.send();

			initUI();
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



}
