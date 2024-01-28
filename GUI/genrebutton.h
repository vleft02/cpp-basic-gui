#pragma once
#include"button.h"
#include "config.h"
#include <iostream>

//Button that selectes a genre we want to filter 
//the entries with
class GenreButton : public Button
{
	//name of the genre
	std::string genre;

	//if a button is clicked it stays selected
	bool selected = false;
	
	//offset used for spacing out the buttons
	int offset=0;
public:

	//set boolean values selected to true or false
	void select() { selected = true; }
	void deSelect() { selected = false; }

	void draw() override;
	
	void action()override;

	//constructor that takes the name of the genre as an input
	GenreButton(std::string c);
};