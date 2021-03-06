#include "Composition.h"
#include "Expand.h"
#include "EconHelper.h"
#include "TaskHelper.h"
#include "CreateCoalition.h"
#include "CoalitionHelper.h"
#include "CompositionHelper.h"

Expand::Expand()
	: builder(nullptr)
{
	taskName = "Expand()";
	taskType = EXP;
}

Expand::~Expand()
{
}

void Expand::assign()
{
	printDebugInfo("Assign");
	createCoalition();
	assigned = true;
	printDebugInfo("Assign End");
}

void Expand::act()
{
	printDebugInfo("Acting");
	acting = true;
	builder->expand();
	printDebugInfo("Acting End");
}

void Expand::update()
{
	printDebugInfo("Update");
	if (complete)
		return;

	if (!assigned)
	{
		assign();
		return;
	}

	if (coalition->isActive())
	{
		if(!builder)
			builder = (*coalition->getAgentSet().begin());

		if ((*coalition->getUnitSet().begin())->exists() && !complete)
			act();
	}

	printDebugInfo("Update End");
}

void Expand::succeed()
{
	complete = true;
	profit = 1.0;
	printDebugInfo("Success!", true);

	EconHelper::doneExpanding();
}

void Expand::fail()
{
	complete = true;
	profit = 0.0;
	printDebugInfo("Failure!", true);

	EconHelper::doneExpanding();
}