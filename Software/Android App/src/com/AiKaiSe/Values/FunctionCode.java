package com.AiKaiSe.Values;

//Enum for all FunctionCodes in LEDPI Project
public enum FunctionCode {

	// Funktion codes
	Handshake(0x0001), 
	VersionInfo(0x0002), 
	Error(0xFFFF), 
	GMODULE(0x0003), 
	MONO_MONO(0x0004), 
	SNAKE_START(0x0005), 
	SNAKE_DIRECTION(0x0006), 
	PHOTO_CHANGE(0x0007),
	BALLS_CHANGE(0x0008),
	PLASMA_CHANGE(0x0009);

	private int value;

	private FunctionCode(int i) {
		this.value = i;
	}

	public int getvalue() {
		return this.value;
	}
}
