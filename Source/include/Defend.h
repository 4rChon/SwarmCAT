#pragma once
#include "Task.h"
#include "MapHelper.h"

class Defend: public Task
{
public:
	//constructors and destructors
	Defend();

	//-
	void assign();
	void act();
	void update();
};