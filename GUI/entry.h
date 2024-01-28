#pragma once
#include "widget.h"
#include <iostream>
#include "interctable.h"

//Entries represent the movies used
//they inherit from interactable because they are clickable in the menu
class Entry :public Interactable
{

	//All the necessary info on the movies 
	std::string title;
	std::string directors;
	std::string actors;
	std::string genre;
	int year;
	std::string image;
	std::string description;
	
	//When an entry is selected an outline needs to be present to signify that fact
	bool selected = false;

public:

	//Setters used to position an entry in the canvas
	//pos_x and pos_y inherited from class Widget
	void setPosX(float x) { if (title != "") pos_x = x; }
	void setPosY(float y) { if (title != "") pos_y = y; }
	
	//set boolean values selected to true or false
	void select() { selected = true; }
	void deSelect() { selected = false; }

	//getter for inherited variable Highlighted
	bool getHighlighted() { return highlighted; }

	//Multiple setters used during the initiation of the catalog
	void setDirectors(std::string directors) { this->directors = directors; };
	void setActors(std::string actors) { this->actors = actors; };
	void setGenre(std::string genre) { this->genre = genre; };
	std::string getGenre() { return genre; };
	void setYear(int year) { this->year = year; };
	int getYear() { return year; };
	void setImage(std::string image) { this->image = image; };
	void setDescription(std::string description) { this->description = description; };
	
	void draw() override;
	void update() override;
	//constructor that takes title of the movie as an entry
	Entry(std::string title);
};