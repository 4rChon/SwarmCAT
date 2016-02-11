#pragma once
#include "BWTA.h"
#include "Producer.h"
#include "Worker.h"

typedef BWAPI::SetContainer < Worker*, std::hash<void*>> Workerset;

class Expand;

class ResourceDepot : public Producer
{
protected:
	BWTA::BaseLocation* baseLocation;
	Workerset workers;
	int mineralMiners;
	int gasMiners;
	bool expandDesire;
public:
	//constructors and destructors
	ResourceDepot();
	ResourceDepot(BWAPI::Unit unit);

	~ResourceDepot();

	//getters
	BWTA::BaseLocation* getBaseLocation();
	Workerset& getWorkers();
	int getMineralMiners();
	int getGasMiners();

	//-
	virtual void act();

	//helpers
	bool isMineralSaturated();
	bool isGasSaturated();
	void addMineralWorker(Worker* worker);
	void addGasWorker(Worker* worker);
	void removeWorker(Worker* worker);
};