#include "app.h"
#include "graphics.h"
#include "config.h"
#include "menu.h"
#include "arrowbutton.h"
#include "button.h"
#include "dropdownbutton.h"
#include "slider.h"
#include "genrebutton.h"
#include "okbutton.h"
#include <iostream>

void App::draw()
{
	//Set up styling options for background
	graphics::Brush br;
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	br.fill_secondary_color[0] = 0.3f;
	br.fill_secondary_color[1] = 0.3f;
	br.fill_secondary_color[2] = 0.3f;
	br.gradient = true;

	//Draw Background
	graphics::drawRect(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT, br);

	//draw() function of Menu object is called
	//if Menu pointer != nullptr
	if (page)
		page->draw();
	
	//iterate through the list of main menu buttons 
	//and call their respective draw functions
	if (!buttonList.empty()) {

		for (Button* button:buttonList) {
			button->draw();
		}

	}
	
	//if focus is not on the Menu the dropdown menu is active
	//so the extra buttons need to be drawn
	//iterate through the list of dropdown menu buttons 
	//and call their respective draw functions
	if (!page->getFocus())
	{

		for (Button* dButton : dButtonList) {
			dButton->draw();
		}
	}

	graphics::MouseState ms;
	graphics::getMouseState(ms);
	//We use the methods of graphics to draw a small disk in the postion of the cursor on the screen
	graphics::drawDisk(graphics::windowToCanvasX((float)ms.cur_pos_x) , graphics::windowToCanvasY((float)ms.cur_pos_y) ,3,br);

}

void App::update()
{
	//While page != null we call the update function of the Menu object
	if (page) {
		page->update();
	}

	//set up cursor
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	//mx and my now hold the coordinates of the cursor on the canvas 
	float mx = graphics::windowToCanvasX((float)ms.cur_pos_x);	
	float my = graphics::windowToCanvasY((float)ms.cur_pos_y);

	//check if the coordinates of the cursor
	//are contained within the space of a button
	//if focus is true we iterate through the main menu buttons
	//else we iterate through the dropdown menu buttons
	if (page->getFocus()) {
		Button* hoverButton = nullptr;
		for (auto button : buttonList) {
			//check if the coordinates of the cursor
			//are contained within the space of a button
			if (button->contains(mx, my)) {
				button->setHighlight(true);
				hoverButton = button;
			}
			else
			{
				//in all cases that the cursor isnt on
				// an entry highlight should be false
				button->setHighlight(false);
			}
		}
		//when button is clicked 
		if (ms.button_left_pressed && hoverButton)
		{

			hoverButton->update();

		}
	}
	else
	{

		Button* hoverButton = nullptr;
		for (auto button : dButtonList) {
			//check if the coordinates of the cursor
			//are contained within the space of a button
			if (button->contains(mx, my)) {
				button->setHighlight(true);
				hoverButton = button;
			}
			else
			{
				button->setHighlight(false);
			}
		}
		//this occurs on the slider buttons
		if (ms.dragging && hoverButton)
		{
			hoverButton->setIsPressed(true);
			hoverButton->update();
		}
		//this occurs on the genre buttons and ok button 
		//when clicked
		if (ms.button_left_pressed && hoverButton)
		{
			hoverButton->update();
		}
		if (ms.button_left_released && hoverButton) 
		{
			hoverButton->setIsPressed(false);
		}
		
	}

}


void App::init()
{
	//Create the Menu object
	page = new Menu();
	//intialize it with init function
	page->init();
	
	//intialize buttons needed and add them to their respective lists
	buttonList.push_back(new ArrowButton('r'));
	buttonList.push_back(new ArrowButton('l'));
	buttonList.push_back(new DropDownButton('d'));
	
	dButtonList.push_back(new DropDownButton('u'));
	dButtonList.push_back(new Slider('f'));
	dButtonList.push_back(new Slider('t'));
	dButtonList.push_back(new GenreButton("drama"));
	dButtonList.push_back(new GenreButton("action"));
	dButtonList.push_back(new GenreButton("crime"));
	dButtonList.push_back(new GenreButton("fantasy"));
	dButtonList.push_back(new GenreButton("scifi"));
	dButtonList.push_back(new GenreButton("history"));
	dButtonList.push_back(new GenreButton("romance"));
	dButtonList.push_back(new GenreButton("thriller"));
	dButtonList.push_back(new OkButton());


	//Set the menu pointer for all the buttons
	for (Button* button : buttonList) 
	{
		button->setMenu(page);
	}

	for (Button* dButton : dButtonList) 
	{
		dButton->setMenu(page);
	}

	//set the font that will be used
	graphics::setFont(std::string(ASSET_PATH) + "texgyreadventor-regular.ttf");
	//Begin playing Music
	graphics::playMusic(std::string(ASSET_PATH) + "music.mp3",0.1f,true,5000);
}




App::~App()
{
	if (page) {
		delete page;
	}
	if (!buttonList.empty()) {
		std::vector<Button*>::iterator buttonIt;
		for (buttonIt = buttonList.begin(); buttonIt != buttonList.end(); ++buttonIt) {
			delete * buttonIt;
		}
	}

}
