#pragma once
#include "button.h"
#include "menu.h"
#include "config.h"

//Arrow button moves the selection by one movie in a specified direction
class ArrowButton :public Button 
{
	
	//Since we have 2 types of arrows
	// a left one and a right one
	//we use this boolean to specify wether
	//the arrow is pointing right or left
	bool right = true;

public:
	void draw() override;

	void action() override;

	//Constructor that sets orientation either 'r' for right or 'l' for left arrow button
	ArrowButton(char orientation);

};