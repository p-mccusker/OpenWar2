#ifndef _PUD_H
#define _PUD_H

#include "src/def.h"
#include "src/Array.h"
#include <vector>

/*
	PUD Class encapsolates a pud file.  
	It has the ability to:
		Load file from specified location
		parse file into distinct data sets which can be used by the engine

*/

struct Map {
	word x, y;
	std::vector<std::vector<SQM>> actionMap;
	std::vector<std::vector<MTXM>> tilesMap;

};

struct Player {
	OWNR owner;
	word sGold, sWood, sOil;
	AIPL ai;
	SIDE race;
	int startSpells;
	int allowedUnitBld, allowedSpells, allowedUpgrd;
	int currSpellUpgrd, currUpgrd;
};

struct Upgrade {
	u_byte upgrdTime;
	word gldCost, lumbrCost, oilCost;
	word upgrdIcon;
	word group;
	int affectFlags; //What does the upgrade give
};

struct Unit {

};

struct PUD
{
	PUD();
	PUD(const char* file);
	~PUD();

	void Load();
	void Save();

	const char* _file;
	Array<Player, 16> _players;

};

#endif
