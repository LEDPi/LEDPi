package com.AiKaiSe.Modul.Plasma;

public enum Method {

	ADD(0x00, "Add"),
	MULTIPLY(0x01, "Multiply"),
	SUBTRACT(0x02, "Subtract"),
	ADDFLAT(0x03, "AddFlat"),
	DIVIDE(0x04, "Divide");
	
	private int value;
	private String name;
	
	private Method(int v, String s){
		this.value = v;
		this.name = s;
	}
	
	public int getValue(){
		return this.value;
	}
	
	public static Method getById(int id){
		for (Method method : values()) {
			if (method.getValue() == id)
				return method;
		}
		return null;
	}
	
	public static String getName(int id){
		Method m = getById(id);
		if (m != null) {
			return m.name;

		}
		return null;
	}
	
}
