#include "dropdownbutton.h"
#include "config.h"
#include "graphics.h"

//when the dropdown menu is opened (down button is clicked) focus is taken away from the main Menu
//so the focus variable is set to true when the dropdown menu is closed (up button is clicked) 
//focus is given back to the main Menu
void DropDownButton::action()
{
	if (orientation == 'u' && !page->getFocus())
	{
		page->setFocus(true);
	}


	else {
		page->setFocus(false);
	}
}

void DropDownButton::draw()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;

	if (highlighted) {
		br.fill_color[1] = 0.5f;
		br.fill_color[2] = 0.5f;
	}

	if (orientation == 'd' && !page->getFocus())
	{
		br.texture = std::string(ASSET_PATH) + img;
		graphics::Brush b;
		b.outline_opacity = 0.0f;
		b.gradient = true;
		b.fill_color[0] = 0.8f;
		b.fill_color[1] = 0.8f;
		b.fill_color[2] = 0.8f;
		b.fill_secondary_color[0] = 0.0f;
		b.fill_secondary_color[1] = 0.0f;
		b.fill_secondary_color[2] = 0.0f;
		graphics::drawRect(CANVAS_WIDTH / 2, 0.0f, 600, 500, b);
	}
	else 
	{
		br.texture = std::string(ASSET_PATH) + img;
		graphics::drawRect(pos_x, pos_y, width, height, br);
	}

}


//depending on the type different attributes are set up
DropDownButton::DropDownButton(char c) 
{
	//d for down 
	if (c == 'd') {
		pos_x = CANVAS_WIDTH / 2;
		pos_y = 20.0f;
		width = 30.0f;
		height = 30.0f;
		orientation = c;
		img = "dropdown.png";

	}
	//u for up
	else if (c == 'u') {
		pos_x = CANVAS_WIDTH / 2;
		pos_y = 250.0f;
		width = 30.0f;
		height = 30.0f;
		orientation = c;
		img = "dropup.png";
	}
}
