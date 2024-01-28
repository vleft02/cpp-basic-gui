#pragma once
#include "button.h"

class Slider :public Button
{
	//describes wether the slider affects the year we want to start from
	//or the year we wont to end at
	char type;
	//the year selected by ther slider
	int year = 0;
	

public:

	void draw() override;
	
	//contains is overriden for the sliding action
	//to be used
	bool contains(float mx, float my)override;

	void action();

	Slider(char c);
};