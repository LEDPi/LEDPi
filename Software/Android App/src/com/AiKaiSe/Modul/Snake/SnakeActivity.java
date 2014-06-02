package com.AiKaiSe.Modul.Snake;

import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.widget.ImageButton;
import android.widget.LinearLayout;

import com.AiKaiSe.LEDPi.BaseActivity;
import com.AiKaiSe.LEDPi.R;
import com.AiKaiSe.LEDPi.R.id;

public class SnakeActivity extends BaseActivity implements OnTouchListener {

	private static final String TAG = SnakeActivity.class.getSimpleName();

	// register Listeners
	ImageButton imageButtonUp;
	ImageButton imageButtonDown;
	ImageButton imageButtonLeft;
	ImageButton imageButtonRight;
	LinearLayout linearLayout;

	SnakeHandler snakeHandler;
	SnakeVector snakeVector;

	private final int TOLERANCE = 30;
	private final double SPACE_DEGREE = 10;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		Log.d(TAG, "onCreate called");
		setContentView(R.layout.activity_snake);
		snakeHandler = new SnakeHandler();
		snakeVector = new SnakeVector();
		setTouchListener();
	}

	public void setTouchListener() {
		linearLayout = (LinearLayout) findViewById(id.LinearLayout);
		linearLayout.setOnTouchListener(this);
		imageButtonUp = (ImageButton) findViewById(R.id.imageButtonUp);
		imageButtonUp.setOnTouchListener(this);
		imageButtonDown = (ImageButton) findViewById(R.id.imageButtonDown);
		imageButtonDown.setOnTouchListener(this);
		imageButtonLeft = (ImageButton) findViewById(R.id.imageButtonLeft);
		imageButtonLeft.setOnTouchListener(this);
		imageButtonRight = (ImageButton) findViewById(R.id.imageButtonRight);
		imageButtonRight.setOnTouchListener(this);
	}

	@Override
	public boolean onTouch(View v, MotionEvent event) {

		if (event.getAction() == MotionEvent.ACTION_DOWN) {
			snakeVector.setStartX(event.getRawX());
			snakeVector.setStartY(event.getRawY());
			return true;
		}

		if (event.getAction() == MotionEvent.ACTION_MOVE) {

			snakeVector.setEndX(event.getRawX());
			snakeVector.setEndY(event.getRawY());

			if (Math.abs(snakeVector.getRelativeX()) > TOLERANCE
					|| Math.abs(snakeVector.getRelativeY()) > TOLERANCE) {
				double angle = snakeVector.getAngle();

				// Up
				if ((angle > (SPACE_DEGREE / 2 + 45))
						&& (angle < (135 - SPACE_DEGREE / 2))) {
					snakeHandler.sendUp();
					Log.d(TAG, "slide UP");
				}

				// Left
				if ((angle > (135 + SPACE_DEGREE / 2))
						&& (angle < (225 - SPACE_DEGREE / 2))) {
					snakeHandler.sendLeft();
					Log.d(TAG, "slide LEFT");
				}

				// Down
				if ((angle > (225 + SPACE_DEGREE / 2))
						&& (angle < (315 - SPACE_DEGREE / 2))) {
					snakeHandler.sendDown();
					Log.d(TAG, "slide DOWN");
				}

				// Right
				if ((angle > (315 + SPACE_DEGREE / 2))
						|| (angle < (45 - SPACE_DEGREE / 2))) {
					snakeHandler.sendRight();
					Log.d(TAG, "slide RIGHT");
				}
			}

			return true;
		}

		if (event.getAction() == MotionEvent.ACTION_UP) {
			return true;
		}
		return false;
	}

}
