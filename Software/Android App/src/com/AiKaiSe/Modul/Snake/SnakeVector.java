package com.AiKaiSe.Modul.Snake;


public class SnakeVector {
	
	private double startX, startY, endX, endY;
	
	public double getStartX() {
		return startX;
	}

	public void setStartX(double startX) {
		this.startX = startX;
	}

	public double getStartY() {
		return startY;
	}

	public void setStartY(double startY) {
		this.startY = startY;
	}

	public double getEndX() {
		return endX;
	}

	public void setEndX(double endX) {
		this.endX = endX;
	}

	public double getEndY() {
		return endY;
	}

	public void setEndY(double endY) {
		this.endY = endY;
	}

	public SnakeVector(){
		this.endX = 0.0;
		this.endY = 0.0;
		this.startX = 0.0;
		this.startY = 0.0;
	}
	
	public double getRelativeX()
	{
		return (endX-startX);
	}
	
	public double getRelativeY()
	{
		return (startY - endY);
	}

	public double getLenght(){
		return  Math.sqrt(Math.pow(getRelativeY(), 2)+Math.pow(getRelativeX(), 2));
	}
	
	public double getAngle(){
		
		//Calculates angle in radian
		double relativeX = this.getRelativeX();
		double relativeY = this.getRelativeY();
	
		double angle_rad = Math.atan2(relativeY,relativeX);
		if(angle_rad<0.0)
		{
			angle_rad += 2*Math.PI;
		}

		//Converts radian to degree	
		double angle_degree = (angle_rad/Math.PI)*180;
		
		return angle_degree;
	}
}
