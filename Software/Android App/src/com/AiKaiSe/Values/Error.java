package com.AiKaiSe.Values;

//Enum for all Errors in this Project.
public enum Error {

	OK(0x00), NOK(0x01), VERSION(0x02), GMODULE(0x03), GMODULE_NA(0x04);

	private int value;

	private Error(int i) {
		this.value = i;
	}

	public int getvalue() {
		return this.value;
	}

}
