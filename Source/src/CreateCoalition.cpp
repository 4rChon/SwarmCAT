#include "CreateCoalition.h"
#include "CoalitionHelper.h"
#include "TaskHelper.h"
#include "EconHelper.h"
#include "CreateUnit.h"

CreateCoalition::CreateCoalition(Composition composition, Task* task)
{
	taskName = "CreateCoalition(Composition, " + task->getName() + ")";
	if (task->getType() == ATT)
	{
		for (auto& unit : composition.getUnitMap())
		{
			if (!unit.first.isBuilding())
				composition.getUnitMap()[unit.first] += (int)(unit.second * EconHelper::getUnitMultiplier());
		}		
	}
	taskCoalition = CoalitionHelper::addCoalition(composition, task);	
	task->setCoalition(taskCoalition);
	cost = composition.getCost();
	taskType = CRC;
	//debug = true;
}

// add coalition to open coalitions
void CreateCoalition::assign()
{	
	printDebugInfo("Assign");
	assigned = true;
	printDebugInfo("Assign End");
}

// attempt to activate coalition
void CreateCoalition::act()
{
	printDebugInfo("Acting");
	Composition differenceComposition = taskCoalition->getTargetComp() - taskCoalition->getCurrentComp();
	for (auto unitType : differenceComposition.getTypes())
	{
		int unitCount = differenceComposition[unitType];
		if (unitType.isWorker())
			continue;
		if (unitCount > 0)
		{			
			//std::cout << "I need " << differenceComposition[unitType] << " more " << unitType.c_str() << "\n";
			CreateUnit *createUnit = new CreateUnit(unitType, unitCount);
			addSubTask(createUnit);
		}
	}
	acting = true;
	printDebugInfo("Acting End");
}

void CreateCoalition::update()
{
	printDebugInfo("Update");
	if (complete)
		return;

	if (!assigned)
	{
		assign();
		return;
	}

	if (taskCoalition->isActive())
	{
		succeed();
		return;
	}

	if (assigned && !acting)
		act();
	//if(age > x) fail();
	//TODO: fail when taking too long
	printDebugInfo("Update End");
}

double CreateCoalition::getCost()
{
	cost = taskCoalition->getTargetComp().getCost() - taskCoalition->getCurrentComp().getCost();
	for (auto task : subTasks)
		cost += task->getCost();

	return cost;
}