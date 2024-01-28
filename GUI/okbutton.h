#pragma once
#include "button.h"

//Button used to apply filters 
//comes up only in the dropdown menu
class OkButton : public Button
{
public:

	void draw() override;

	void action() override;
	OkButton();
};