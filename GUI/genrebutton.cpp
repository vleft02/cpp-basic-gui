#include "genrebutton.h"
#include "config.h"
#include "graphics.h"

//when a genre button is selected they are pushed to the genre list located in the menu object
//if they are deselected they should be removed
void GenreButton::action()
{
	if (!selected) {
		select();
		(page->getGenres())->push_back(genre);

	}
	else {
		deSelect();
		(page->getGenres())->remove(genre);
	}
	
}

void GenreButton::draw()
{
	graphics::Brush Buttonbr;
	graphics::Brush textBr;
	textBr.fill_color[0] = 0.0f;
	textBr.fill_color[1] = 0.0f;
	textBr.fill_color[2] = 0.0f;
	Buttonbr.outline_color[0] = 0.0f;
	Buttonbr.outline_color[1] = 0.0f;
	Buttonbr.outline_color[2] = 0.0f;
	textBr.outline_opacity = 0.0f;
	if (selected || highlighted) {
		Buttonbr.fill_color[1] = 0.5f;
		Buttonbr.fill_color[2] = 0.5f;
	}
	graphics::drawRect(pos_x, pos_y, width, height, Buttonbr);
	graphics::drawText(pos_x - offset, pos_y + 2, 15, genre, textBr);
	graphics::drawText(CANVAS_WIDTH / 2 + 170, 20, 15, "Genre: ", textBr);

}



//Different attributes set for each genre
GenreButton::GenreButton(std::string c)
{


	if (c == "drama") {
		pos_x = CANVAS_WIDTH / 2 + 259;
		pos_y = 40;
		width = 55;
		height = 20;
		genre = c;
		offset = 23;
	}
	else if (c == "romance") {
		pos_x = CANVAS_WIDTH / 2 + 250;
		pos_y = 65;
		width = 72;
		height = 20;
		genre = c;
		offset = 30;
	}
	else if (c == "crime") {
		pos_x = CANVAS_WIDTH / 2 + 260;
		pos_y = 90;
		width = 50;
		height = 20;
		genre = c;
		offset = 19;
	}
	else if (c == "fantasy") {
		pos_x = CANVAS_WIDTH / 2 + 195;
		pos_y = 40;
		width = 60;
		height = 20;
		genre = c;
		offset = 25;
	}
	else if (c == "scifi") {
		pos_x = CANVAS_WIDTH / 2 + 187;
		pos_y = 65;
		width = 42;
		height = 20;
		genre = c;
		offset = 14;
	}
	else if (c == "history") {
		pos_x = CANVAS_WIDTH / 2 + 197;
		pos_y = 90;
		width = 60;
		height = 20;
		genre = c;
		offset = 23;
	}
	else if (c == "action")
	{
		pos_x = CANVAS_WIDTH / 2 + 194;
		pos_y = 115;
		width = 53;
		height = 20;
		genre = c;
		offset = 23;
	}
	else if (c == "thriller")
	{
		pos_x = CANVAS_WIDTH / 2 + 258;
		pos_y = 115;
		width = 62;
		height = 20;
		genre = c;
		offset = 30;
	}
}