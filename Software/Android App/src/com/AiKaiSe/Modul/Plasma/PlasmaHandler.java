package com.AiKaiSe.Modul.Plasma;

import android.util.Log;

import com.AiKaiSe.LEDPi.StartActivity;
import com.AiKaiSe.Network.Message;
import com.AiKaiSe.Values.FunctionCode;


public class PlasmaHandler {

	private static final String TAG = PlasmaHandler.class.getSimpleName();
	
	private Method method = Method.ADD;
	private Color color = Color.REDGREEN;

	private float ConcentricScale = 2500;
	private float ConcentricSpeed = 4;
	private float Period = 0.418879f;
	private float Speed = 0.1f;

	private boolean Invert = false;
	

	public void send(){
		//DEBUG ausgabe
		Log.e(TAG, "spinnerMethod: " + method);
		Log.e(TAG, "spinnerColor: " + color);
		Log.e(TAG, "ConcentricScale: " + ConcentricScale);
		Log.e(TAG, "ConcentricSpeed: " + ConcentricSpeed);
		Log.e(TAG, "Period: " + Period);
		Log.e(TAG, "Speed: " + Speed);
		Log.e(TAG, "Invert: " + Invert);
		
		byte[] data = new byte [17];
		
		//Pack Message in Byte array
		//FLAG
		////Invert
		if(Invert){
			data[0] |= 0x80;
		}
		////Method
		data[0] |= (method.getValue() & 0x07) << 2;
		////Color
		data[0] |= (color.getValue() & 0x03);
		//Concentric Scale
		System.arraycopy(floatToByte(ConcentricScale), 0, data, 1, 4);
		//Concentric Speed
		System.arraycopy(floatToByte(ConcentricSpeed), 0, data, 5, 4);
		//Period
		System.arraycopy(floatToByte(Period), 0, data, 9, 4);
		//Speed
		System.arraycopy(floatToByte(Speed), 0, data, 13, 4);
		
		StartActivity.comunicationHandler.send(FunctionCode.PLASMA_CHANGE, data);
		
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
		
		
		Message receiveMessage= StartActivity.comunicationHandler.sendrequest(FunctionCode.PLASMA_CHANGE, null);
		
//		
//		if(Invert){
//			data[0] |= 0x80;
//		}
//		////Method
//		data[0] |= (method.getValue() & 0x07) << 2;
//		////Color
//		data[0] |= (color.getValue() & 0x03);
		
		//FLAG
		////Color

		////Invert
		Invert = (receiveMessage.data[0] & 0x80) > 0;
		
		//Method
		method = Method.getById((receiveMessage.data[0] & 0x1C )>> 2) ;
		//Color
		color =  Color.getById(receiveMessage.data[0] & 0x03)  ;
				
		//Concentric Scale
		ConcentricScale = byteToFloat(receiveMessage.data, 1);
		//Concentric Speed
		ConcentricSpeed = byteToFloat(receiveMessage.data, 5);
		//Period
		Period = byteToFloat(receiveMessage.data, 9);
		//Speed
		Speed = byteToFloat(receiveMessage.data, 13);
	
		Log.e(TAG, "spinnerMethod: " + method);
		Log.e(TAG, "spinnerColor: " + color);
		Log.e(TAG, "ConcentricScale: " + ConcentricScale);
		Log.e(TAG, "ConcentricSpeed: " + ConcentricSpeed);
		Log.e(TAG, "Period: " + Period);
		Log.e(TAG, "Speed: " + Speed);
		Log.e(TAG, "Invert: " + Invert);
		
	}
	
	//-----------------------------------------------------------------------------------------------------
	
	public Method getMethod() {
		return method;
	}

	public void setMethod(Method method) {
		this.method = method;
		send();
	}

	public Color getColor() {
		return color;
	}

	public void setColor(Color color) {
		this.color = color;
		send();
	}

	public float getConcentricScale() {
		return ConcentricScale;
	}

	public void setConcentricScale(float concentricScale) {
		ConcentricScale = concentricScale;
		send();
	}

	public float getConcentricSpeed() {
		return ConcentricSpeed;
	}

	public void setConcentricSpeed(float concentricSpeed) {
		ConcentricSpeed = concentricSpeed;
		send();
	}

	public float getPeriod() {
		return Period;
	}

	public void setPeriod(float period) {
		Period = period;
		send();
	}

	public float getSpeed() {
		return Speed;
	}

	public void setSpeed(float speed) {
		Speed = speed;
		send();
	}

	public boolean isInvert() {
		return Invert;
	}

	public void setInvert(boolean invert) {
		Invert = invert;
		send();
	}






}
