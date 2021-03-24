#ifndef _PUD_H
#define _PUD_H
#pragma once
#include "def.h"

/*
	PUD Class encapsolates a pud file.
	It has the ability to:
		Load file from specified location
		parse file into distinct data sets which can be used by the engine

*/

template<typename S, typename T>
bool contains(const S& item, const T& container){
	for (auto& it : container){
		if (it == item)
			return true;
	}
	return false;
}

template <typename T>
void readFromArray(const T& src, int &startPos, T& dest, const int& cnt){
	for (int i = 0; i < cnt; i++){
		dest[i] = src[startPos + i];
	}
	startPos += cnt;
}

template <typename T>
void bytesToType(std::string& buffer, int &startPos, T& dest){
	dest = *(T*)&buffer[startPos];
	startPos += sizeof(T);
}

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
	int4 startSpells;
	int4 allowedUnitBld, allowedSpells, allowedUpgrd;
	int4 currSpellUpgrd, currUpgrd;
};

struct Upgrade {
	byte upgrdTime;
	word gldCost, lumbrCost, oilCost;
	word upgrdIcon;
	word group;
	int4 affectFlags; //What does the upgrade give
};

struct Unit {
	MISSILE missle;
	UNIT_TYPE type;
	SECOND_ACTION secondAction; //Only first 58 units, anything may cause crash
	int4 unitSize,
		 boxSize,//X then Y;
		 sight;

	word overlapFrames,
		 hp,
		 pntVal, // Points for killing unit
		 xCoord,
		 yCoord,
		 capacity; // if gold mine/oil well contain 2500 * this, otherwise 0 passive 1 active

	byte bldTime,
		atkRange,
		reactRangeCmp,
		reactRangePlyr,
		armor,
		priority,
		dmg_basic,
		dmg_piercing,
		cmpAnnoyFactor,
		owner;



	////////////Special Cases/////////
	int4 flags;
	/// \brief flags
	/// bit 0: Land unit
	/// bit 1: Air unit
	/// bit 2: Explode when killed (used on catapult)
	/// bit 3: Sea unit
	/// bit 4: Critter
	/// bit 5: Is a building
	/// bit 6: Is a submarine
	/// bit 7: Can see submarine
	/// bit 8: Is a peon
	/// bit 9: Is a tanker
	/// bit10: Is a transport
	/// bit11: Is a place to get oil
	/// bit12: Is a storage for gold
	/// bit13: Not used
	/// bit14: Can ground attack (only applies to catapult and
	/// 	   ships)
	/// bit15: Is undead (exorcism work on them)
	/// bit16: Is a Shore building
	/// bit17: Can cast spell
	/// bit18: Is a storage for wood
	/// bit19: Can attack
	/// bit20: Is a tower
	/// bit21: Is an oil patch
	/// bit22: Is a mine
	/// bit23: Is a hero
	/// bit24: Is a storage for oil
	/// bit25: Is invisibility/unholy armor kill this unit
	/// bit26: Is this unit act like a mage
	/// bit27: Is this unit organic (spells)
	/// bit28: not used
	/// bit29: not used
	/// bit30: not used
	/// bit31: not used
	///

	byte gldCost, // 1/10 gold cost
		lumbrCost, // ^
		oilCost, // ^
		decayRate, // dies in rate * 6 sec, 0 for never decays
		canTarget; // 1: land, 2: sea, 4: air, OR together

	//Booleans
	byte magic,//0 or 1
		selectable, //0 or 1
		weaponsUpgradable,
		armorUpgradable;

	//////////////////


};

struct fileSection{
	std::string title = "    ";
	int startPos = 0,
		endPos = 0,
		size = 0;
};

using oilConcentrationMap = std::vector<std::vector<word>>;

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
	Array<word*, 508> udtaUnused;
	Array<word*, 127> udtaSwampFrames;
	oilConcentrationMap oilMap;

	std::vector<fileSection> sections;
	//////////
};

void findSectionHeaders(PUD& pud, const std::string& buffer);

class FILE_NOT_FOUND {};

#endif
