package com.AiKaiSe.Modul.Snake;


//Enum for all Maps in Snake Modul
public enum SnakeMap {

	// Map codes
	Empty_Map(0x01), One_Border(0x02), Maze_One(0x03), Maze_Two(0x04);

	private int value;

	private SnakeMap(int i) {
		this.value = i;
	}

	public int getvalue() {
		return this.value;
	}

}
