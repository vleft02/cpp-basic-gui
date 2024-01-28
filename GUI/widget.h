#pragma once

//abstract class widget describes a general object of the GUI
class Widget
{
protected:	
	//The nessecary aspects of every widget of the application
	float pos_x = 0;
	float pos_y = 0;
	float width = 0;
	float height = 0;
	
	
	//basic functions used for the graphical objects
	virtual void draw()=0;
	virtual void update()=0;
};