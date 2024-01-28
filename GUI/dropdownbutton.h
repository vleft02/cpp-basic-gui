#pragma once
#include"button.h"
#include "config.h"

//Open and close the dropdown menu 
class DropDownButton : public Button
{
	//'u' or 'd' for up and down
	//down opens the menu
	//up closes it
	char orientation = 'd';
	bool pressed = false;
	//image used for the button
	std::string img = "";
public:
	void action()override;

	void draw() override;

	//constructor with a char as input that seperates the button 
	//that opens and closes the dropdown menu
	DropDownButton(char c);
};