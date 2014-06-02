package com.AiKaiSe.Modul.Snake;

//Enum for all Direction in Snake Modul
public enum SnakeDirection {

	// Drections
	UP(0x01), RIGHT(0x02), DOWN(0x03), LEFT(0x04);

	private int value;

	private SnakeDirection(int i) {
		this.value = i;
	}

	public int getvalue() {
		return this.value;
	}
}
