#pragma once
#include "menu.h"
#include "arrowbutton.h"
#include "config.h"
#include <vector>

//The base class for the application (first to be called)
//Does things like create a menu object initialize buttons
//and implemnts cursor actions
class App
{
	//pointer to the menu of movies nullptr at first
	Menu * page = nullptr;


	//list with all the main menu buttons 
	//to be iterated for drawing and updating
	//initializeed during App::init()
	std::vector<Button*> buttonList;

	//same idea as above but used for the buttons tha need to be printed if the
	//dropdown menu is active
	//initialized during App::init()
	std::vector<Button*> dButtonList;

public:

	//basic functions used
	void draw();
	void update();
	void init();
	
	~App();
};