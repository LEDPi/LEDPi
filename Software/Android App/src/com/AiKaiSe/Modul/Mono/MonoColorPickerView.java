package com.AiKaiSe.Modul.Mono;

import android.content.Context;
import android.content.SharedPreferences;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.RectF;
import android.graphics.Shader;
import android.graphics.SweepGradient;
import android.preference.PreferenceManager;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;

class MonoColorPickerView extends View {
	
	private static final String TAG = MonoColorPickerView.class.getSimpleName();

	private Paint bigCirclePaint;
	private Paint smallMiddleCirclePaint;
	private final int[] colors;

	private float centerX = 540;
	private float centerY = 540;

	// Radius kleiner kreis innen ...
	private float CENTER_RADIUS = 50;

	private float strokeWidthBigCircle = 50;
	private float strokeWidthsmallMiddleCircle = 200;

	private boolean mTrackingCenter;
	private boolean mHighlightCenter;

	private final float PI = 3.1415926f;

	int smallMiddleCircleInitialColor;

	MonoHandler monoHandler;
	Context myContext;

	MonoColorPickerView(Context c, MonoOnColorChangedListener l, MonoHandler mm,
			Context context) {
		super(c);

		myContext = context;
		monoHandler = mm;

		centerX = dpToPx(160);
		centerY = dpToPx(150);
		CENTER_RADIUS = dpToPx(50);
		strokeWidthBigCircle = dpToPx(50);
		strokeWidthsmallMiddleCircle = dpToPx(200);

		// zeichnen des Farb Gradienten um ein Zentralen Punkt.
		colors = new int[] { 0xFFFF0000, 0xFFFF00FF, 0xFF0000FF, 0xFF00FFFF,
				0xFF00FF00, 0xFFFFFF00, 0xFFFF0000 };
		Shader shader = new SweepGradient(0, 0, colors, null);

		bigCirclePaint = new Paint(Paint.ANTI_ALIAS_FLAG);
		bigCirclePaint.setShader(shader);
		bigCirclePaint.setStyle(Paint.Style.STROKE);

		bigCirclePaint.setStrokeWidth(strokeWidthBigCircle); // Dicke des
																// Äußeren
																// Kreises

		smallMiddleCirclePaint = new Paint(Paint.ANTI_ALIAS_FLAG);
		smallMiddleCirclePaint.setColor(smallMiddleCircleInitialColor);
		smallMiddleCirclePaint.setStrokeWidth(strokeWidthsmallMiddleCircle);

		SharedPreferences preferences = PreferenceManager
				.getDefaultSharedPreferences(myContext);
		int depth = preferences.getInt("depth", 255);
		int r = (int) (((double) 255 / (double) depth) * monoHandler.rgb[0]);
		int g = (int) (((double) 255 / (double) depth) * monoHandler.rgb[1]);
		int b = (int) (((double) 255 / (double) depth) * monoHandler.rgb[2]);

		smallMiddleCirclePaint.setColor(Color.rgb(r, g, b));
	}

	private int dpToPx(int dp) {
		float density = this.getContext().getResources().getDisplayMetrics().density;
		return Math.round(dp * density);
	}

	@Override
	protected void onDraw(Canvas canvas) {
		canvas.drawColor(255);
		float r = centerX - bigCirclePaint.getStrokeWidth();

		canvas.translate(centerX, centerX);

		canvas.drawOval(new RectF(-r, -r, r, r), bigCirclePaint);
		// canvas.drawPaint(bigCirclePaint);
		canvas.drawCircle(0, 0, CENTER_RADIUS, smallMiddleCirclePaint);

		if (mTrackingCenter) {
			int c = smallMiddleCirclePaint.getColor();
			smallMiddleCirclePaint.setStyle(Paint.Style.STROKE);

			if (mHighlightCenter) {
				smallMiddleCirclePaint.setAlpha(0xFF);
			} else {
				smallMiddleCirclePaint.setAlpha(0x80);
			}

			smallMiddleCirclePaint.setStyle(Paint.Style.FILL);
			smallMiddleCirclePaint.setColor(c);
		}
	}

	private int ave(int s, int d, float p) {
		return s + java.lang.Math.round(p * (d - s));
	}

	private int interpColor(int colors[], float unit) {
		if (unit <= 0) {
			return colors[0];
		}
		if (unit >= 1) {
			return colors[colors.length - 1];
		}

		float p = unit * (colors.length - 1);
		int i = (int) p;
		p -= i;

		// now p is just the fractional part [0...1) and i is the index
		int c0 = colors[i];
		int c1 = colors[i + 1];
		int a = ave(Color.alpha(c0), Color.alpha(c1), p);
		int r = ave(Color.red(c0), Color.red(c1), p);
		int g = ave(Color.green(c0), Color.green(c1), p);
		int b = ave(Color.blue(c0), Color.blue(c1), p);

		return Color.argb(a, r, g, b);
	}

	private int[] getrgb(int colors[], float unit) {

		float p = unit * (colors.length - 1);
		int i = (int) p;
		p -= i;

		// now p is just the fractional part [0...1) and i is the index
		int c0 = colors[i];
		int c1 = colors[i + 1];
		// int a = ave(Color.alpha(c0), Color.alpha(c1), p);
		int r = ave(Color.red(c0), Color.red(c1), p);
		int g = ave(Color.green(c0), Color.green(c1), p);
		int b = ave(Color.blue(c0), Color.blue(c1), p);

		SharedPreferences preferences = PreferenceManager
				.getDefaultSharedPreferences(myContext);
		int depth = preferences.getInt("depth", 255);

		r = (int) (((double) depth / (double) 255) * r);
		g = (int) (((double) depth / (double) 255) * g);
		b = (int) (((double) depth / (double) 255) * b);

		int[] temprgb = new int[] { r, g, b };

		return temprgb;
	}

	@Override
	public boolean onTouchEvent(MotionEvent event) {
		float x = event.getX() - centerX;
		float y = event.getY() - centerY;
		boolean inCenter = java.lang.Math.sqrt(x * x + y * y) <= CENTER_RADIUS;

		switch (event.getAction()) {
		case MotionEvent.ACTION_DOWN:
			mTrackingCenter = inCenter;
			if (inCenter) {
				mHighlightCenter = true;
				invalidate();

				break;
			}
		case MotionEvent.ACTION_MOVE:
			if (mTrackingCenter) {
				if (mHighlightCenter != inCenter) {
					mHighlightCenter = inCenter;
					invalidate();
				}

			} else {
				float angle = (float) java.lang.Math.atan2(y, x);
				// need to turn angle [-PI ... PI] into unit [0....1]
				float unit = angle / (2 * PI);
				if (unit < 0) {
					unit += 1;
				}
				smallMiddleCirclePaint.setColor(interpColor(colors, unit));
				invalidate();

				Log.d(TAG, "Color circle touched");

				monoHandler.setRGB(getrgb(colors, unit));
				monoHandler.send();
				// Aktionen am Äußeren Kreis on Touch
			}
			break;
		case MotionEvent.ACTION_UP:
			if (mTrackingCenter) {
				if (inCenter) {
					// aktion on klick in den Mittelkreis ...
				}
				mTrackingCenter = false; // so we draw w/o halo
				invalidate();
			}
			break;
		}
		return true;
	}
}