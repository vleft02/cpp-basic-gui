#include "menu.h"
#include "graphics.h"
#include "config.h"
#include <iostream>
#include "pugixml.hpp"
#include <string>
#include <chrono>
#include <thread>


//Move x entries through the page 
//right (+) or left (-)
//used for selecting entries with the cursor
void Menu::advance(int x)
{
	//x negative means we move left
	if (x < 0) {
		//call prev() x times
		for (int i = x; x < 0; x++) {
			prev();
		}
	}
	//x positive means we move right
	else if(x>0)
	{
		//call next() x times
		for (int i = x; x > 0; x--) {
			next();
		}
	}
	//if x = 0 nothing should happen
}

//find movies with wanted characteristics add them to the searchList
//and set filtered to True
void Menu::filter() 
{
	//Deselect the cuurently selected entry 
	if (!(filtered && searchList.size() == 4))
	{
	(*currEntry)->deSelect();
	}

	std::list<Entry*>::iterator it;
	if (genres.empty())
	{
		if (fromYear == 1972 && toYear == 2008) {
			//years.clear();
			//if no genres were selected to filter
			//we use the film list like we would normally do 
			it = filmList.begin();
			std::advance(it, 2);
			//set the first element to draw
			drawStart = it;
			//Since we want to start with the movie in the middle selected we
			//advance the iterator by 2 entries so it points to the middle entry
			std::advance(it, 2);
			//we select the middle entry
			(*it)->select();
			//currEntry now points to the middle entry
			currEntry = it;
			std::advance(it, 3);
			drawEnd = it;
			setFiltered(false);
			return;
		}
		else
		{
			//Empty out the list to insert new movies 
			searchList.clear();
			//check for entries with matching characteristics
			for (Entry* entry : filmList)
			{
				if (fromYear <= entry->getYear() && toYear >= entry->getYear())
				{
					searchList.push_back(entry);
				}
			}
			setFiltered(true);
		}
		
	}
	else
	{
		//Empty out the list to insert new movies 
		searchList.clear();
		//check for entries with matching characteristics
		for (Entry* entry : filmList)
		{
			for (std::string genre : genres)
			{
				if ((entry->getGenre()).find(genre) != std::string::npos && fromYear <= entry->getYear() && toYear >= entry->getYear() && std::find(searchList.begin(), searchList.end(), entry) == searchList.end())
				{
					searchList.push_back(entry);
				}
			}
		}
		setFiltered(true);
	}

	//As in the basic filmList two empty entries are pushed to
	//each side as padding for the wanted format
	searchList.push_back(new Entry(""));
	searchList.push_back(new Entry(""));
	searchList.push_front(new Entry(""));
	searchList.push_front(new Entry(""));


	it = searchList.begin();
	//skip empty entries
	std::advance(it, 2);
	//set the first element to draw
	drawStart = it;
	
	//Since we want to start with the movie in the middle selected we
	//advance the iterator by 2 entries so it points to the middle entry
	if (searchList.size() == 4)
	{
		return;
	}
	else if (searchList.size() < 8)
	{
		it = searchList.begin();
		
		//if we have only one movie we want to also draw the empty entries for correct alignment
		if (searchList.size() !=5){ drawStart = ++it; }
		else
		{
			drawStart = searchList.begin();
		}

		std::advance(it, 2);
		//we select the middle entry
		(*it)->select();
		//currEntry now points to the middle entry
		currEntry = it;

		//set the last element to draw
		drawEnd = --searchList.end();
	}
	else
	{
		std::advance(it, 2);
		//we select the middle entry
		(*it)->select();
		//currEntry now points to the middle entry
		currEntry = it;

		//under this condition there are three movies left to fill the page
		//so to fill the page we draw until the fifth entry
		std::advance(it, 3);
		//set the last element to draw
		drawEnd = it;
	}
	//we select the middle entry
}

//set the years we want to filter with called 
//in the slider update() function
void Menu::setYear(int year, char c)
{
	//f stands for from
	if (c == 'f')
	{
		fromYear = year;

	}
	//else if 't' stands for to
	else 
	{
		toYear = year;
	}

}

//scroll to the right of the list
void Menu::next()
{
	graphics::playSound(std::string(ASSET_PATH) + "snd.mp3", 100.0f, true);

	if (!filtered)
	{
	//since we use empty entries as padding for the gui to look better
	// we need to make sure we are not pointing to these empty entries
	//found at the start and at the end of the list 
		if (currEntry != --(--(--filmList.end()))) {
			(*currEntry)->deSelect();
			++currEntry;
			(*currEntry)->select();
			++drawStart;
			++drawEnd;
		}
	}
	else {
	//since we use empty entries as padding for the gui to look better
	// we need to make sure we are not pointing to these empty entries
	//found at the start and at the end of the list 
		if (currEntry != --(--(--searchList.end())))
		{
			(*currEntry)->deSelect();
			++currEntry;
			(*currEntry)->select();
			//if size less than 9 then we dont want to 
			//cahnge the drawstart and drawend vars because the page isnt full
			if (!searchList.size() < 9)
			{
				++drawStart;
				++drawEnd;
			}
		}
	}
}

//scroll to the left of the list
void Menu::prev()
{
	graphics::playSound(std::string(ASSET_PATH) + "snd.mp3", 100.0f, false);

	if (!filtered) {
	//since we use empty entries as padding for the gui to look better
	// we need to make sure we are not pointing to these empty entries
	//found at the start and at the end of the list 
		if (currEntry != ++(++(filmList.begin()))) 
		{
			(*currEntry)->deSelect();
			--currEntry;
			(*currEntry)->select();
			--drawStart;
			--drawEnd;
		}
	}
	else 
	{
	//since we use empty entries as padding for the gui to look better
	// we need to make sure we are not pointing to these empty entries
	//found at the start and at the end of the list 
		if (currEntry != ++(++(searchList.begin()))) 
		{
			(*currEntry)->deSelect();
			--currEntry;
			(*currEntry)->select();
			//if size less than 9 then we dont want to 
			//cahnge the drawstart and drawend vars because the page isnt full
			if (!searchList.size()<9) 
			{
				--drawStart;
				--drawEnd;
			}

		}
	}
}


void Menu::draw()
{
	// iterator of our list filmList which contains pointers to entries
	std::list<Entry*>::iterator it;
	// we use this integer later to make the entrie shown evenly spaced out
	int positioningPrefix = 450;
	// When the program first runs the first entry is selected
	//Draw the indexing of the page
	graphics::Brush br;
		
	

	if (filtered && searchList.size() == 4)
	{
		graphics::Brush br;
		graphics::drawText(CANVAS_WIDTH / 2 - 80, CANVAS_HEIGHT / 2 + 40, 22, " No Results Found  :( ", br);
		br.texture = std::string(ASSET_PATH) + "face.png";
		br.outline_opacity = 0.0f;
		graphics::drawRect(CANVAS_WIDTH / 2 + 5, CANVAS_HEIGHT / 2 - 75, 120, 120, br);
	}
	else 
	{
		for (it = drawStart; it != drawEnd; ++it) {
			(*it)->setPosX(CANVAS_WIDTH / 2 - positioningPrefix);
			(*it)->setPosY(CANVAS_HEIGHT / 2 - 70);
			positioningPrefix = positioningPrefix - 225;
			(*it)->draw();
		}	
	}

		positioningPrefix = 0;
		
}

//Depending on which fifth of the page the 
//cursor is located c_pos takes the values below
void Menu::setCursorPosition(int mx)
{

	if (mx > 0 && mx < CANVAS_WIDTH / 5) {
		c_pos = -2;
	}
	else if (mx > CANVAS_WIDTH / 5 && mx < 2 * CANVAS_WIDTH / 5) {
		c_pos = -1;
	}
	else if (mx > 2 * CANVAS_WIDTH / 5 && mx < 3 * CANVAS_WIDTH / 5) {
		c_pos = 0;
	}
	else if (mx > 3 * CANVAS_WIDTH / 5 && mx < 4 * CANVAS_WIDTH / 5) {
		c_pos = 1;
	}
	else {
		c_pos = 2;
	}
	//values are then given to the advance() method to move by the appropriate steps
}


void Menu::update()
{
	
	//if page is focused we dont want to give the user the ability to scroll
	if(focus){
		//get Starting time
		float startTime = graphics::getDeltaTime();
		//set up cursor
		graphics::MouseState ms;
		graphics::getMouseState(ms);
		//mx and my now hold the coordinates of the cursor on the canvas 
		float mx = graphics::windowToCanvasX((float)ms.cur_pos_x);
		float my = graphics::windowToCanvasY((float)ms.cur_pos_y);

		if (graphics::getKeyState(graphics::SCANCODE_RIGHT))
		{
			//scroll one entry to the right 
			next();
		}

		if (graphics::getKeyState(graphics::SCANCODE_LEFT))
		{
			//scroll one entry to the left
			prev();
		}

		//points to the entry that the cursor hovers over
		Entry* hoveredEntry = nullptr;
		//points to the appropriate list
		//depending on if we have active filters or not 
		std::list<Entry*> listPointer;

		//if page not filtered
		//we want the basic filmList
		if (!filtered) {
			listPointer = filmList;
		}
		//else we want the filterd searchList
		else
		{
			listPointer = searchList;
		}

		//we set the value of the c_pos variable
		//to use int the code below
		setCursorPosition(mx);

		//iterate through the list of entries
		for (auto entry : listPointer)
		{
			entry->update();
			if (entry->getHighlighted() == true) 
			{
				hoveredEntry = entry;
			}
			
		}
		//when entry is clicked 
		if (ms.button_left_pressed && hoveredEntry)
		{
			//call Menu::advance() method
			advance(c_pos);
		}



		//if time passed is less than 50ms wait for 75ms
		//used so the scrolling speed isnt based on each computers performance
		if (graphics::getDeltaTime() - startTime < 50) std::this_thread::sleep_for(std::chrono::milliseconds(75));
	}
}


//We read the films.xml document containing all the info about the film
//insert them to the filmlist and initialize the pointers that point to it for the menu
void Menu::init()
{
	pugi::xml_document doc;
	doc.load_file("assets\\films.xml");
	std::list<Entry*>::iterator it;
	
	//we create elements by giving them a title using the 
	//appropriate constructor
	for (auto& n : doc.select_nodes("//collection/film/@title")) {
		filmList.push_back(new Entry(n.attribute().value()));
	}
	
	//We make list iterator it point to the begining of the list 
	//and iterate through it to fill out each entry attribute by attribute 
	it = filmList.begin();
	for (auto& n : doc.select_nodes("//collection/film/@directors")) {
		(*it)->setDirectors(n.attribute().value());
		++it;
	}

	it = filmList.begin();
	for (auto& n : doc.select_nodes("//collection/film/@actors")) {;
		(*it)->setActors(n.attribute().value());
		++it;
	}

	it = filmList.begin();
	for (auto& n : doc.select_nodes("//collection/film/@genre")) {
		(*it)->setGenre(n.attribute().value());
		++it;
	}
	
	it = filmList.begin();
	for (auto& n : doc.select_nodes("//collection/film/@year")) {
		//the year is inserted as a string but we want it as an int
		//so we use stoi to convert it 
		std::string temp = n.attribute().value();
		int tempYear = 0;
		if (temp != "") 
		{
			tempYear = std::stoi(temp);
		}
		(*it)->setYear(tempYear);
		++it;
	}
	
	it = filmList.begin();
	for (auto& n : doc.select_nodes("//collection/film/@image")) {
		(*it)->setImage(std::string(ASSET_PATH) + n.attribute().value());
		++it;
	}
	
	it = filmList.begin();
	for (auto& n : doc.select_nodes("//collection/film/@description")) {
		(*it)->setDescription(n.attribute().value());
		++it;
	}
	

	
	//The first two entries are blank and are used as padding
	//for the menu to look better
	it = filmList.begin();
	std::advance(it, 2);
	//set the first element to draw
	drawStart = it;
	//Since we want to start with the movie in the middle selected we
	//advance the iterator by 2 entries so it points to the middle entry
	std::advance(it, 2);
	//we select the middle entry
	(*it)->select();
	//currEntry now points to the middle entry
	currEntry = it;
	std::advance(it, 3);
	drawEnd = it;

	return;
}
