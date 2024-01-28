#include "slider.h" 
#include "graphics.h" 
#include "config.h" 

void Slider::draw()
{
	graphics::Brush br;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;

	//If t we have a slider that sets the year we ant to reach "To: " 
	if (type == 't') 
	{	
		graphics::drawLine(CANVAS_WIDTH / 2 - 290, pos_y, CANVAS_WIDTH / 2 - 110, pos_y, br);
		graphics::drawText(CANVAS_WIDTH / 2 - 290, pos_y - 20, 12, "To:", br);
		if (highlighted)
		{
			br.fill_color[1] = 0.5f;
			br.fill_color[2] = 0.5f;
		}
		graphics::drawRect(pos_x, pos_y, width, height, br);
	}
	//If f we have a slider that sets the year we want to start from "From: " 
	else if(type == 'f') {
		graphics::drawLine(CANVAS_WIDTH / 2 - 290, pos_y , CANVAS_WIDTH / 2 - 110, pos_y, br);
		graphics::drawText(CANVAS_WIDTH / 2 - 290, pos_y - 20, 12, "From:", br);
		if (highlighted)
		{
			br.fill_color[1] = 0.5f;
			br.fill_color[2] = 0.5f;
		}
		graphics::drawRect(pos_x, pos_y , width, height, br);
	}
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;

	//draw the selected year
	graphics::drawText(CANVAS_WIDTH / 2 - 250, pos_y - 20, 12, std::to_string(year), br);

}



bool Slider::contains(float mx, float my)
{
	//when the button is pressed (held down i.e when dragging) 
	//we have a different sensitivity so that we cant drag both sliders at the same time
	if (isPressed) 
	{
		return (mx >= CANVAS_WIDTH/2 - 293 && mx <= CANVAS_WIDTH/2 - 103 ) && (my >= pos_y -20 && my <= pos_y +20);
	}
	else 
	{
		return (mx >= pos_x - width / 2 - 5 && mx <= pos_x + width / 2 + 5) && (my >= pos_y - height / 2 && my <= pos_y + height / 2);
	}
}

//move the button based on the cursors horizontal position 
void Slider::action()
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);

	//if cursor reaches out of bounds the maximun or minimum position is set
	if (graphics::windowToCanvasX((float)ms.cur_pos_x) > CANVAS_WIDTH / 2 - 110)
	{
		pos_x = CANVAS_WIDTH / 2 - 110;
	}
	else if (graphics::windowToCanvasX((float)ms.cur_pos_x) < CANVAS_WIDTH / 2 - 290)
	{
		pos_x = CANVAS_WIDTH / 2 - 290;
	}

	//else we are within bounds and the cursor x coordinate is given to the slider
	else
	{
		pos_x = graphics::windowToCanvasX((float)ms.cur_pos_x);
	}

	//Each 5 canvas units corresponds to 1 year
	//310 is equal to CANVAS_WIDTH/2 - 290
	year = 1972 + (pos_x - 310) / 5;
	page->setYear(year, type);
}

//Construct the sliders based on their type 
Slider::Slider(char c)
{

	//f as in from
	if (c == 'f') {
		pos_x = CANVAS_WIDTH / 2 - 290;
		pos_y = 100;
		year = 1972;
	}
	//t as in to
	else if (c == 't') 
	{
		pos_x = CANVAS_WIDTH / 2 - 110;
		pos_y = 140;
		year = 2008;
	}

	width = 7;
	height = 14;
	type = c;
}
