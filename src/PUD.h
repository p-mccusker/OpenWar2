#ifndef _PUD_H
#define _PUD_H

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
void readFromArray(std::vector<pud::byte>& src, int &startPos, T& dest, const int& cnt){
	for (int i = 0; i < cnt; i++){
		dest[i] = src[startPos + i];
	}
	startPos += cnt;
}

template <typename T>
void bytesToType(pud::byte *buffer, int &startPos, T& dest){
	dest = *(T*)&buffer[startPos];
	startPos += sizeof(T);
}

template <typename T>
void printHex(const T arr[], const int& start, const int& end){
	for (int i = start; i <= end; i++){
		std::cout << "0x" << std::setfill('0') << std::setw(2) << std::right << std::hex << (int)arr[i] << ' ';
		//std::cout << std::hex << (int)buffer[i] << ' ';
		if (i - start % 12 == 0) // 12 cols
			std::cout << '\n';
	}

	std::cout << std::dec << ' ';
}

struct Type {
	std::array<pud::byte, 2> mapNum; // 'WAR2 MAP' + 00 00
	std::array<pud::byte, 2> unused; //Set to $0a and $ff by editor
	std::array<pud::byte, 4> tag; //Checked for consistency in multiplayer
};



using ActionMap = std::vector<pud::word>;
using TileMap = std::vector<pud::word>;



struct Map {
	pud::word x, y;
	ActionMap actionMap;
	TileMap tilesMap;
	bool standardSize;
};

void isMapStdSize(Map& map);

struct allowed {
	pud::int4 allowedUnitBld,
		startSpells,
		allowedSpells,
		currSpellsUpgrading,
		allowedUpgrade,
		currUpgrading;
};

struct Player {
	using owner = pud::byte;
	using side = pud::byte;
	using aipl = pud::byte;
	owner ownr;
	pud::word sGold, sWood, sOil;
	aipl ai;
	side race;
	allowed techTree;
};

struct Upgrade {

	pud::byte upgrdTime;
	pud::word gldCost, lumbrCost, oilCost;
	pud::word upgrdIcon;
	pud::word group;
	pud::int4 affectFlags; //What does the upgrade give
};

struct Unit {
	using missile = pud::byte;
	using unit_type = pud::byte;
	using second_action = pud::byte;
	using unit = pud::word;
	std::string name;
	missile missle;
	unit_type type;
	unit kind;
	second_action secondAction; //Only first 58 units, anything may cause crash
	pud::int4 unitSize,
		 boxSize,//X then Y;
		 sight;

	pud::word overlapFrame,
		 hp,
		 pntVal, // Points for killing unit
		 xCoord,
		 yCoord,
		 capacity; // if gold mine/oil well contain 2500 * this, otherwise 0 passive 1 active

	pud::byte bldTime,
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
	pud::int4 flags;
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

	pud::byte gldCost, // 1/10 gold cost
		lumbrCost, // ^
		oilCost, // ^
		decayRate, // dies in rate * 6 sec, 0 for never decays
		canTarget; // 1: land, 2: sea, 4: air, OR together

	//Booleans
	pud::byte magic,//0 or 1
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
	std::vector<pud::byte> data;
};

using oilConcentrationMap = std::vector<pud::word>;

struct PUD
{
	PUD();
	PUD(const std::string& file, uint64_t addr = NULL);
	~PUD();

	void Load();
	void Save(const std::string& outFile);

	using era_ = pud::word;
	using ver_ = pud::word;

	//Members///
	std::array<Player, 16> players;
	std::array<pud::word, 508> udtaUnused;
	std::array<pud::word, 127> udtaSwampFrames;
	std::array<Unit, 110> unitData;
	std::array<Upgrade, 52> upgrades;

	std::vector<Unit> currentUnits;
	std::vector<fileSection> sections;
	oilConcentrationMap oilConcentration;

	std::string desc;
	std::string file;

	Type mapType;
	Map map;
	
	uint64_t startAddr;

	era_ terrain;
	ver_ ver;
	pud::word defaultUnitData;
	pud::word defaultUpgradeData;
	//////////
};

void findSectionHeaders(PUD& pud, const std::string& buffer);

class FILE_NOT_FOUND {};

#endif
