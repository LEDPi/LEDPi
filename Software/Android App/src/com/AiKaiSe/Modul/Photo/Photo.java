package com.AiKaiSe.Modul.Photo;

//Enum for all Photos in Snake Modul
public enum Photo {

	// Photo codes
	PhotoPi(0x01), Linux(0x02), Android_1(0x03), Android_2(0x04), Smiley(0x05);

	private int value;

	private Photo(int i) {
		this.value = i;
	}

	public int getvalue() {
		return this.value;
	}

}