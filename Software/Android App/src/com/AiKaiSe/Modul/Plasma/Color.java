package com.AiKaiSe.Modul.Plasma;


public enum Color {

	REDGREEN(0x00, "RedGreen"),
	GREENBLUE(0x01, "GreenBlue"),
	RGB(0x02, "RGB"),
	GREY(0x03, "Grey");
	
	
	private int value;
	private String name;
	
	private Color(int v, String s){
		this.value = v;
		this.name = s;
	}
	
	public int getValue(){
		return this.value;
	}
	
	public static Color getById(int id){
		for (Color color : values()) {
			if (color.getValue() == id)
				return color;
		}
		return null;
	}
	
	public static String getName(int id){
		Color c = getById(id);
		if (c != null) {
			return c.name;

		}
		return null;
	}
	
}
