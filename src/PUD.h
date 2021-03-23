#ifndef _PUD_H
#define _PUD_H

#include "def.h"
#include "Array.h"
#include <vector>

/*
	PUD Class encapsolates a pud file.  
	It has the ability to:
		Load file from specified location
		parse file into distinct data sets which can be used by the engine

*/

struct Type {
	Array<byte, 2> mapNum; // 'WAR2 MAP' + 00 00
	Array<byte, 2> unused; //Set to $0a and $ff by editor
	Array<byte, 4> tag; //Checked for consistency in multiplayer
};

using ActionMap = std::vector<std::vector<SQM>>;
using TileMap = std::vector<std::vector<MTXM>>;

struct Map {
	word x, y;
	ActionMap actionMap;
	TileMap tilesMap;

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
	byte upgrdTime;
	word gldCost, lumbrCost, oilCost;
	word upgrdIcon;
	word group;
	int affectFlags; //What does the upgrade give
};

struct Unit {
	word overlapFrames;
	int sight;
	word hp;
	MISSILE missle;
	UNIT_TYPE type;
	SECOND_ACTION secondAction; //Only first 58 units, anything may cause crash
	std::bitset<32> unitSize,
					boxSize;//X then Y;

	//Left off: pntVal

	// Special Cases
	byte gldCost, // 1/10 gold cost
		lumbrCost, // ^
		oilCost, // ^
		decayRate; // dies in rate * 6 sec, 0 for never decays

	//////////////////

	byte bldTime,
		atkRange,
		reactRangeCmp,
		reactRangePlyr,
		armor,
		priority,
		dmg_basic,
		dmg_piercing;


	
	byte
		cmpAnnoyFactor;

	//Booleans
	byte magic,//0 or 1
		selectable, //0 or 1
		weaponsUpgradable,
		armorUpgradable;



};

struct PUD
{
	PUD();
	PUD(const std::string& file);
	~PUD();

	void Load();
	void Save();

	
	//Members///
	Array<Player, 16> _players;
	word _terrain;
	VER_ _ver;
	std::string _desc[32];
	std::string _file;
	//////////
};

#endif
