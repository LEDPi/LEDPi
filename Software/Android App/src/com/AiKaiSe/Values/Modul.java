package com.AiKaiSe.Values;

import com.AiKaiSe.Modul.Ball.BallActivity;
import com.AiKaiSe.Modul.Mono.MonoActivity;
import com.AiKaiSe.Modul.Photo.PhotoActivity;
import com.AiKaiSe.Modul.Plasma.PlasmaActivity;
import com.AiKaiSe.Modul.Snake.SnakeMapActivity;

//Enum for all Moduls in LEDPI Project
public enum Modul {

	MUX(0x0001, "MUX", null), 
	COM(0x0002, "COM", null), 
	GUI(0x0004, "GUI", null), 
	GMM(0x0008, "GMM", null), 
	STREAM(0x0010, "STREAM", null), 
	BARS(0x0020, "BARS", null), 
	MONO(0x0040, "MONO", MonoActivity.class), 
	SNAKE(0x0100, "SNAKE", SnakeMapActivity.class), 
	PHOTO(0x200, "PHOTO", PhotoActivity.class), 
	Balls(0x0400, "BALLS", BallActivity.class), 
	PLASMA(0x0080, "PLASMA", PlasmaActivity.class);

	private int value;
	private String name;
	private Class c;

	private Modul(int i, String name, Class cl) {
		this.value = i;
		this.name = name;
		this.c = cl;
	}

	private Modul(int i, String name) {
		this.value = i;
		this.name = name;
		this.c = null;
	}

	public static Class getActivity(int id) {
		Modul m = getById(id);
		if (m != null) {
			if (m.c != null) {
				return m.c;
			}
		}
		return null;
	}

	public int getvalue() {
		return this.value;
	}

	public static Modul getById(long id) {
		for (Modul modul : values()) {
			if (modul.getvalue() == id)
				return modul;
		}
		return null;
	}

	public static String getName(int id) {
		Modul m = getById(id);
		if (m != null) {
			return m.name;

		}
		return null;
	}

	public static boolean hasUserInterface(int id) {
		Modul m = getById(id);
		if (m != null) {
			if (m.c != null) {
				return true;
			}
		}
		return false;
	}

}
