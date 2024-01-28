#pragma once
#include "widget.h"
#include <list>
#include "entry.h"
#include <vector>



class Menu
{
	//if focus is false only items of the dropdown menu can be interacted with
	//if focus is true all items can be interacted with
	bool focus = true;
	
	//if this variable is true it means that certain methods 
	//such as next and prev need to use the searchList 
	//instead of the filmList
	bool filtered = false;

	//cursor position is (-2, -1, 0, 1, 2) for each fifth of the page 
	//depending on which part of the page the cursor is different behaviors need to occur
	//this is used to realize which entry is clicked and advnace the selection appropriately
	int c_pos = 0;

	//basic list of films
	std::list<Entry*> filmList;
	//subtotal of filmList used for filtering
	std::list<Entry*> searchList;

	//years used for filtering
	int fromYear = 1972;
	int toYear = 2008;
	//list of genres used for filtering
	std::list<std::string> genres;

	//pointer to a specific entry pointer in the entry list
	//used to show which movie is selected
	std::list<Entry*>::iterator currEntry;

	//Pointer to where the first entry to be drawn is
	//
	std::list<Entry*>::iterator drawStart;
	std::list<Entry*>::iterator drawEnd;

	//counter used 
	int counter = 0;


public:

	//advance film list currEntry by x entries
	void advance(int x);

	//Scrolling through page
	void next();
	void prev();

	//setter and getter used for boolean variable focus
	void setFocus(bool b) { focus = b; }
	bool getFocus() { return focus; }
	void setFiltered(bool b) { filtered = b; }

	void filter();

	//sets the c_pos variable 
	void setCursorPosition(int mx);

	//char c defines wether we are setting fromYear or toYear
	void setYear(int year, char c);


	std::list<std::string>* getGenres() { return &genres; };
	//int* getYears() { return years; }
	//
	void draw();
	void update();
	void init();
};