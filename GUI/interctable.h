#pragma once
#include "widget.h"
//Another abstract class that inherits from widget 
//with the Addition of some methods and extra variables
//to make it possible to inetract with it using the cursor
class Interactable : public Widget
{
public:
	bool getIsPressed() { return isPressed; }
	void setIsPressed(bool b) { isPressed = b; }
	
	//used for interaction with the cursor 
	//if cursor coordinates are contained within 
	//the limits of the widget true is returned 
	virtual bool contains(float mx, float my) { return (mx >= pos_x - width / 2 && mx <= pos_x + width / 2) && (my >= pos_y - height / 2 && my <= pos_y + height / 2); }
	
	//set highlighted to true if cursor hovers over button
	virtual void setHighlight(bool h) { highlighted = h; };
protected:
	//if is highlighted is set to true 
	//an if statement is fulfiled in the draw() funtion of the respective class
	bool highlighted = false;
	
	//set to true if the left mouse button is held 
	bool isPressed = false;

	//basic graphical object funtions 
	virtual void draw() = 0;
	virtual void update() = 0;

};