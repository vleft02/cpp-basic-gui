#pragma once
#include <iostream>
#include "interctable.h"
#include "menu.h"

//child of class Interactable that also has a pointer to the Menu object so that 
//the respective action of the button can affect the Menu
class Button :public Interactable
{
public:
	//set a pointer to the Menu object used for interacting with the menu 
	//by pressing a button
	virtual void setMenu(Menu* c) { page = c; }

	virtual void draw() override = 0;
	//all the buttons call the action() method when updated
	virtual void update() override { action(); };


	//the behavior of a button when pressed
	virtual void action() = 0;
protected:
	//We use this pointer so that the actions
	//caused by pressing these buttons can affect the page
	Menu* page = nullptr;
};