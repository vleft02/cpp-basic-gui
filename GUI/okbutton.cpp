#include "okbutton.h"
#include "config.h"
#include "graphics.h"

void OkButton::draw()
{	

	graphics::Brush buttonBr;
	graphics::Brush textBr;
	buttonBr.outline_color[0] = 0.0f;
	buttonBr.outline_color[1] = 0.0f;
	buttonBr.outline_color[2] = 0.0f;
	if (highlighted) {
		buttonBr.fill_color[1] = 0.5f;
		buttonBr.fill_color[2] = 0.5f;
	}
	textBr.fill_color[0] = 0.0f;
	textBr.fill_color[1] = 0.0f;
	textBr.fill_color[2] = 0.0f;
	textBr.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, width, height, buttonBr);
	graphics::drawText(CANVAS_WIDTH / 2 + 266, 224, 15, "ok ", textBr);

}



//Give focus back to the main menu and call Menu::filter() method
void OkButton::action()
{
	page->setFocus(true);
	page->filter();
}

OkButton::OkButton()
{
	pos_x = CANVAS_WIDTH / 2 + 275;
	pos_y = 220;
	width = 25;
	height = 20;
}
