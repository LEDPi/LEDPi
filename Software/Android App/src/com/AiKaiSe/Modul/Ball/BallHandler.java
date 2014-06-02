package com.AiKaiSe.Modul.Ball;

import android.util.Log;

import com.AiKaiSe.LEDPi.StartActivity;
import com.AiKaiSe.Network.Message;
import com.AiKaiSe.Values.FunctionCode;


public class BallHandler {

	private static final String TAG = BallHandler.class.getSimpleName();
	
	private int Ball = 4;
	private float Speed = 1.2f;
	private float Red = 1;
	private float Green = 0.2f;
	private float Blue = 0.7f;
	private float Size = 8;
	private float Glow = 0.4f;
	private float RandomSpeed = 4;

	private boolean Invert = false;
	private boolean Random = false;
	
	
	public void send(){
//		//DEBUG ausgabe !!
//		Log.e(TAG, "Ball: " + Ball);
//		Log.e(TAG, "Speed: " + Speed);
//		Log.e(TAG, "Red: " + Red);
//		Log.e(TAG, "Green: " + Green);
//		Log.e(TAG, "Blue: " + Blue);
//		Log.e(TAG, "Size: " + Size);
//		Log.e(TAG, "Glow: " + Glow);
//		Log.e(TAG, "RandomSpeed: " + RandomSpeed);
//		Log.e(TAG, "Invert: " + Invert);
//		Log.e(TAG, "Random: " + Random);
//		
		byte[] data = new byte [29];
		
		//Pack Message in Byte array
		//FLAG
		////Color
		if(Random){
			data[0] |= 0x80;
		}
		////Invert
		if(Invert){
			data[0] |= 0x40;
		}
		////Number of Balls
		data[0] |= (Ball & 0x0F);
		////Speed
		System.arraycopy(floatToByte(Speed), 0, data, 1, 4);
		////Red
		System.arraycopy(floatToByte(Red), 0, data, 5, 4);
		////Green
		System.arraycopy(floatToByte(Green), 0, data, 9, 4);
		////Blue
		System.arraycopy(floatToByte(Blue), 0, data, 13, 4);
		////Size
		System.arraycopy(floatToByte(Size), 0, data, 17, 4);
		////Glow
		System.arraycopy(floatToByte(Glow), 0, data, 21, 4);
		////RandomSpeed
		System.arraycopy(floatToByte(RandomSpeed), 0, data, 25, 4);
		
		//Send Message
		StartActivity.comunicationHandler.send(FunctionCode.BALLS_CHANGE, data);
		
	}
	

	
	private byte[] floatToByte(float value){
		
		int bits = Float.floatToIntBits(value);
		byte[] bytes = new byte[4];
		bytes[0] = (byte)(bits & 0xff);
		bytes[1] = (byte)((bits >> 8) & 0xff);
		bytes[2] = (byte)((bits >> 16) & 0xff);
		bytes[3] = (byte)((bits >> 24) & 0xff);
			
		return bytes;
	}
	
	private float byteToFloat(byte[] b, int offset){
		int t = 0;
		t = t | ((byte) -102);
	
		int bits = 	(((int) b[offset + 0]) & 0xff) 		|
					(((int) b[offset + 1]) & 0xff) << 8	| 
					(((int) b[offset + 2]) & 0xff) << 16| 
					(((int) b[offset + 3]) & 0xff) << 24 ; 
		
		return Float.intBitsToFloat(bits);
	}
	
	public void receiveState(){
		Message receiveMessage= StartActivity.comunicationHandler.sendrequest(FunctionCode.BALLS_CHANGE, null);
		
		
		//FLAG
		////Color
		Random = (receiveMessage.data[0] & 0x80) > 0;
		////Invert
		Invert = (receiveMessage.data[0] & 0x40) > 0;
		////Number of Balls
		Ball = receiveMessage.data[0] & 0x0F;
		////Speed
		Speed = byteToFloat(receiveMessage.data, 1);
		////Red
		Red = byteToFloat(receiveMessage.data, 5);
		////Green
		Green = byteToFloat(receiveMessage.data, 9);
		////Blue
		Blue = byteToFloat(receiveMessage.data, 13);
		////Size
		Size = byteToFloat(receiveMessage.data, 17);
		////Glow
		Glow = byteToFloat(receiveMessage.data, 21);
		////RandomSpeed
		RandomSpeed = byteToFloat(receiveMessage.data, 25);
		
		//DEBUG ausgabe !!
		Log.e(TAG, "Ball: " + Ball);
		Log.e(TAG, "Speed: " + Speed);
		Log.e(TAG, "Red: " + Red);
		Log.e(TAG, "Green: " + Green);
		Log.e(TAG, "Blue: " + Blue);
		Log.e(TAG, "Size: " + Size);
		Log.e(TAG, "Glow: " + Glow);
		Log.e(TAG, "RandomSpeed: " + RandomSpeed);
		Log.e(TAG, "Invert: " + Invert);
		Log.e(TAG, "Random: " + Random);
		
	}
	
	//----------------------------------------------------------------------------------------------
	
	public int getBall() {
		return Ball;
	}

	public void setBall(int ball) {
		Ball = ball;
		send();
	}

	public float getSpeed() {
		return Speed;
	}

	public void setSpeed(float speed) {
		Speed = speed;
		send();
	}

	public float getRed() {
		return Red;
	}

	public void setRed(float red) {
		Red = red;
		send();
	}

	public float getGreen() {
		return Green;
	}

	public void setGreen(float green) {
		Green = green;
		send();
	}

	public float getBlue() {
		return Blue;
	}

	public void setBlue(float blue) {
		Blue = blue;
		send();
	}

	public float getSize() {
		return Size;
	}

	public void setSize(float size) {
		Size = size;
		send();
	}

	public float getGlow() {
		return Glow;
	}

	public void setGlow(float glow) {
		Glow = glow;
		send();
	}

	public float getRandomSpeed() {
		return RandomSpeed;
	}

	public void setRandomSpeed(float randomSpeed) {
		RandomSpeed = randomSpeed;
		send();
	}

	public boolean isInvert() {
		return Invert;
	}

	public void setInvert(boolean invert) {
		Invert = invert;
		send();
	}

	public boolean isRandom() {
		return Random;
	}

	public void setRandom(boolean random) {
		Random = random;
		send();
	}
	
	public void test(){

		float t1 = 1.2f;
		float t2 = 1.0f;
		float t3 = 0.2f;
		float t4 = 4.0f;
		float t5 = 0.4f;
		
		float erg1 = byteToFloat( floatToByte(t1), 0);
		float erg2 = byteToFloat( floatToByte(t2), 0);
		float erg3 = byteToFloat( floatToByte(t3), 0);
		float erg4 = byteToFloat( floatToByte(t4), 0);
		float erg5 = byteToFloat( floatToByte(t5), 0);
	}

}
