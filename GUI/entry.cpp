#include "entry.h"
#include "graphics.h"
#include "config.h"
#include <iostream>

void Entry::draw()
{
	if (title != ""){
		graphics::Brush br;
		float scale = 1;
		br.outline_opacity = 0.0f;
		if (selected || highlighted)
		{
			//simple outline on selected entry
			br.outline_opacity = 10.0f;
			br.outline_color[0] = 0.9f;
			br.outline_color[1] = 0.9f;
			br.outline_color[2] = 0.9f;
			br.gradient = true;
		
			if (selected) {
				//Draw info of selected Movie
				graphics::drawText(CANVAS_WIDTH / 2 - 560, CANVAS_HEIGHT / 2 + 195, 17, "Director: " + directors, br);
				graphics::drawText(CANVAS_WIDTH / 2 - 310, CANVAS_HEIGHT / 2 + 195, 17, "Actors: " + actors, br);
				graphics::drawText(CANVAS_WIDTH / 2 + 180, CANVAS_HEIGHT / 2 + 195, 17, "Year: " + std::to_string(year), br);
				graphics::drawText(CANVAS_WIDTH / 2 + 280, CANVAS_HEIGHT / 2 + 195, 17, "Genres: " + genre, br);

				//without the definition of description size a dangling pointer exception is thrown
				size_t descriptionSize = description.size();
				//if size of the description is too large we split it in half plus the characters until we reach a space
				if (descriptionSize > 80) {
					descriptionSize = descriptionSize / 2;
					while (description.at(descriptionSize) !=  ' ')
					{
						descriptionSize++;
					}
					graphics::drawText(CANVAS_WIDTH / 2 - 560, CANVAS_HEIGHT / 2 + 240, 17, ("Description: " + description.substr(0, descriptionSize)).c_str(), br);
					graphics::drawText(CANVAS_WIDTH / 2 - 560, CANVAS_HEIGHT / 2 + 260, 17, description.substr(descriptionSize, description.size()-1).c_str(), br);
				}
				else {
					graphics::drawText(CANVAS_WIDTH / 2 - 560, CANVAS_HEIGHT / 2 + 240, 17, ("Description: " + description).c_str(), br);
				}
			
			}

			scale = 1.2f;
		}

		//Draw movie poster in the position set up in menu.h
		//scale variable defined for changing the size when a movie is selected
		br.texture = image;
		graphics::drawRect(pos_x , pos_y,width * scale,height * scale,br);

		//If c_str() is not used for variable of type std::string an exception is thrown
		//drawing text...
		size_t titleSize = title.size();

		//if size of the title is too large we split it in half plus the characters until we reach a space
		if (titleSize > 20) {
			titleSize = titleSize / 2;
			while (title.at(titleSize) != ' ')
			{
				titleSize++;
			}
			graphics::drawText(pos_x - 70, pos_y + 185, 16, title.substr(0, titleSize).c_str(), br);
			graphics::drawText(pos_x - 70, pos_y + 205, 16, title.substr(titleSize, title.size() - 1).c_str(), br);
		}
		else {
			graphics::drawText(pos_x - 40, pos_y + 185, 16, title.c_str(), br);
		}
	}
}

void Entry::update()
{
	//set up cursor
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	//mx and my now hold the coordinates of the cursor on the canvas 
	float mx = graphics::windowToCanvasX((float)ms.cur_pos_x);
	float my = graphics::windowToCanvasY((float)ms.cur_pos_y);
	
	//check if the coordinates of the cursor
	//are contained within the dimensions of an entry
	if (contains(mx, my)) {
		setHighlight(true);
	}
	else
	{
		//in all cases that the cursor isnt on
		// an entry highlight should be false
		setHighlight(false);
	}
}

//Set the attributes below
Entry::Entry(std::string title) {
	this->title = title;
	if (title == "")
	{
		width = 0;
		height = 0;

	}
	else 
	{
		width = 150;
		height = 280;
	}
}