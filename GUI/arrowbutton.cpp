#include "arrowbutton.h"
#include "graphics.h"
#include "config.h"
#include <iostream>


void ArrowButton::draw() {
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "rarrow.png";
	br.outline_opacity = 0.0f;
	if (!right)
	{
		br.texture = std::string(ASSET_PATH) + "larrow.png";
	}
	if (highlighted) {
		br.fill_color[1] = 0.5f;
		br.fill_color[2] = 0.5f;
	}

	if (isPressed) br.fill_opacity = 0.8f;
	graphics::drawRect(pos_x ,pos_y,width,height,br);}

//move one step depending on the direction of the arrow
void ArrowButton::action()
{
	//we call the next or prev functions
	//through the pointer to the Menu object used
	if (right)
	{
		page->next();
	}
	else
	{
		page->prev();
	}
}


//Different attributes set for each orientaion
ArrowButton::ArrowButton(char orientation) {
	if (orientation == 'r') 
	{ 
		right = true;
		pos_x = CANVAS_WIDTH / 2 + 570;
		pos_y = CANVAS_HEIGHT / 2 - 50;
	}
	else if (orientation == 'l') 
	{
		right = false; 
		pos_x = CANVAS_WIDTH / 2 - 570;
		pos_y = CANVAS_HEIGHT / 2 - 50;
	}
	width = 32;
	height = 32;
}
