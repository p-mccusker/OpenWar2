#pragma once

#include "def.h"

/*
	PUD Class encapsolates a pud file.
	It has the ability to:
		Load file from specified location
		parse file into distinct data sets which can be used by the engine

*/

//Section Headers
const std::vector<std::string> HEADERS = { "TYPE", "VER ", "DESC", "OWNR", "ERA ", "ERAX", "DIM ", "UDTA", "ALOW", "UGRD", "SIDE",
											"SGLD", "SLBR", "SOIL", "AIPL", "MTXM", "SQM ", "OILM", "REGM", "UNIT" };

enum VER_ { HEROES_NO = 0x11, HEROES_YES = 0x13 };

enum OWNR {
	PASSIVE_COMP_PLAYER = 0x02, NO_PLAYER = 0x03, COMP_PLAYER = 0x04, HUMAN_PLAYER = 0x05, RESCUE_PASSIVE = 0x06,
	RESCUE_ACTIVE = 0x07
};

enum ERA_ { FOREST_TYPE = 0x00, WINTER_TYPE = 0x01, WASTELAND_TYPE = 0x02, SWAMP_TYPE = 0x03 };

enum SIDE { HUMAN = 0x00, ORC = 0x01, NEUTRAL = 0x02 };

//Test for values
enum SGLD {
	P1_GOLD, P2_GOLD, P3_GOLD, P4_GOLD, P5_GOLD, P6_GOLD, P7_GOLD, P8_GOLD, P9_GOLD, P10_GOLD, P11_GOLD, P12_GOLD,
	P13_GOLD, P14_GOLD, P15_GOLD, P16_GOLD
};

enum UNIT {
	INFANTRY = 0x00, GRUNT = 0x01, PEASANT = 0x02, PEON = 0x03, BALLISTA = 0x04,
	CATAPULT = 0x05, KNIGHT = 0x06,
	OGRE = 0x07, ARCHER = 0x08, AXETHROWER = 0x09, MAGE = 0x0a, DEATHKNIGHT = 0x0b,
	PALADIN = 0x0c, OGREMAGE = 0x0d, DWARVES = 0x0e, SAPPER = 0x0f, ATTK_PEASANT = 0x10,
	ATTK_PEON = 0x11, RANGER = 0x12, BERSERKER = 0x13, ALLERIA = 0x14, TERON = 0x15,
	KURDAN = 0x16, DENTARG = 0x17, KHADGAR = 0x18, GROM = 0x19, H_TANKER = 0x1a,
	O_TANKER = 0x01b, H_TRANSPORT = 0x1c, O_TRANSPORT = 0x1d, H_DESTROYER = 0x1e, O_DESTROYER = 0x1f,
	BATTLESHIP = 0x20, JUGGERNAUGHT = 0x21, DEATHWING = 0x23, SUBMARINE = 0x26, TURTLE = 0x27,
	FLYING_MACHINE = 0x28, ZEPPLIN = 0x29, GRYPHON = 0x2a, DRAGON = 0x2b, TURALYON = 0x2c,
	EYE_KILROGG = 0x2d, DANATH = 0x2e, KNORGATH = 0x2f, CHOGALL = 0x31, LOTHAR = 0x32,
	GULDAN = 0x33, UTHER = 0x34, ZULJIN = 0x35, SKELETON = 0x37, DAEMON = 0x38,
	CRITTER = 0x39, H_FARM = 0x3a, O_FARM = 0x3b, H_BARRACKS = 0x3c, O_BARRACKS = 0x3d,
	CHURCH = 0x3e, ALTAR = 0x3f, H_SCOUT_TOWER = 0x40, O_SCOUT_TOWER = 0x41, STABLE = 0x42,
	OGREMOUND = 0x43, INVENTOR = 0x44, ALCHEMIST = 0x45, AVIARY = 0x46, ROOST = 0x47,
	H_SHIPYARD = 0x48, O_SHIPYARD = 0x49, H_HALL = 0x4a, O_HALL = 0x4b, H_MILL = 0x4c,
	O_MILL = 0x4d, H_FOUNDRY = 0x4e, O_FOUNDRY = 0x4f, MAGE_TOWER = 0x50, TEMPLE_DAMNED = 0x51,
	H_BLACKSMITH = 0x52, O_BLACKSMITH = 0x53, H_REFINERY = 0x54, O_REFINERY = 0x55, H_OIL_WELL = 0x56,
	O_OIL_WELL = 0x57, H_KEEP = 0x58, O_STRONGHOLD = 0x59, H_CASTLE = 0x5a, O_FORTRESS = 0x5b,
	GOLD = 0x5c, OIL = 0x5d, H_START = 0x5e, O_START = 0x5f, H_GUARD_TOWER = 0x60,
	O_GUARD_TOWER = 0x61, H_CANNON_TOWER = 0x62, O_CANNON_TOWER = 0x63, CIRCLE_POWER = 0x64, PORTAL = 0x65,
	RUNESTONE = 0x66, H_WALL = 0x67, O_WALL = 0x68, NONE_UNIT
};

const static std::vector<pud::word> units =
{ INFANTRY, GRUNT, PEASANT, PEON, BALLISTA, CATAPULT,	KNIGHT, OGRE, ARCHER, AXETHROWER, MAGE,	DEATHKNIGHT, PALADIN, OGREMAGE,
	DWARVES, SAPPER, ATTK_PEASANT, ATTK_PEON, RANGER, BERSERKER, ALLERIA, TERON, KURDAN, DENTARG, KHADGAR, GROM, H_TANKER, O_TANKER,
	H_TRANSPORT, O_TRANSPORT, H_DESTROYER, O_DESTROYER,	BATTLESHIP,	JUGGERNAUGHT, DEATHWING, SUBMARINE,	TURTLE,	FLYING_MACHINE,	ZEPPLIN,
	GRYPHON, DRAGON, TURALYON, EYE_KILROGG,	DANATH,	KNORGATH, CHOGALL, LOTHAR, GULDAN, UTHER, ZULJIN, SKELETON,	DAEMON,	CRITTER, H_FARM,
	O_FARM,	H_BARRACKS, O_BARRACKS,	CHURCH,	ALTAR, H_SCOUT_TOWER, O_SCOUT_TOWER, STABLE, OGREMOUND, INVENTOR, ALCHEMIST, AVIARY, ROOST,
	H_SHIPYARD, O_SHIPYARD,	H_HALL, O_HALL,	H_MILL,	O_MILL,	H_FOUNDRY, O_FOUNDRY, MAGE_TOWER, TEMPLE_DAMNED, H_BLACKSMITH, O_BLACKSMITH,
	H_REFINERY,	O_REFINERY,	H_OIL_WELL,	O_OIL_WELL,	H_KEEP, O_STRONGHOLD, H_CASTLE,	O_FORTRESS, GOLD, OIL, H_START,	O_START,
	H_GUARD_TOWER,	O_GUARD_TOWER, H_CANNON_TOWER, O_CANNON_TOWER, CIRCLE_POWER, PORTAL, RUNESTONE, H_WALL,	O_WALL
};


enum UGRD {
	SW_1 = 0x00, SW_2 = 0x01, AXE_1 = 0x02, AXE_2 = 0x03, ARROW_1 = 0x04,
	ARROW_2 = 0x05, SPEAR_1 = 0x06, SPEAR_2 = 0x07, H_SHIELD_1 = 0x08, H_SHIELD_2 = 0x09,
	O_SHIELD_1 = 0x0a, O_SHIELD_2 = 0x0b, H_CANNON_1 = 0x0c, H_CANNON_2 = 0x0d, O_CANNON_1 = 0x0e,
	O_CANNON_2 = 0x0f, H_SHIP_ARMOR_1 = 0x10, H_SHIP_ARMOR_2 = 0x11, O_SHIP_ARMOR_1 = 0x12, O_SHIP_ARMOR_2 = 0x13,
	CATAPULT_1 = 0x14, CATAPULT_2 = 0x15, BALLISTA_1 = 0x16, BALLISTA_2 = 0x17, RANGERS = 0x18,
	LONGBOW = 0x19, RANG_SCOUTING = 0x1a, RANG_MARKS = 0x1b, BESERKERS = 0x1c, LIGHT_AXES = 0x1d,
	BERS_SCOUTING = 0x1e, BERS_REGEN = 0x1f, TRAIN_OGRE_MAGE = 0x20, TRAIN_PALADIN = 0x21, HOLY_VIS = 0x22,
	HEALING = 0x23, EXOCISM = 0x24, FLAME_SHIELD = 0x25, FIREBALL = 0x26, SLOW = 0x27,
	INVISIBILITY = 0x28, POLYMORPH = 0x29, BLIZZARD = 0x2a, CAST_EYE_KILROGG = 0x2b, BLOODLUST = 0x2c,
	RAISE_DEAD = 0x2d, DEATH_COIL = 0x2e, WHIRLWIND = 0x2f, HASTE = 0x30, UNHOLY_ARMOR = 0x31,
	RUNES = 0x32, DEATH_DECAY = 0x33
};

enum AIPL {
	AI_NEUT = 0x0, AI_0, AI_1, AI_2, AI_3, AI_4, AI_5, AI_6, AI_7,
	///*Unusable* AI
	AI_8, AI_9, AI_10, AI_11, AI_12, AI_13, AI_14, AI_15
};

enum MTXM {  };

enum SQM {
	BRIDGE = 0x0000, LAND = 0x0001, COAST_CNR = 0x0002, DIRT = 0x0011, WATER = 0x0040, FOREST_MOUNT = 0x0081, COAST = 0x0082, WALLS = 0x008d,
	//0x0fxx		 //0x02xx
	SPACE = 0x0f00, CAVE = 0x0200
};

enum REGM { REG_WATER = 0x0000, REG_LAND = 0x4000, REG_ISLAND = 0xfaff, REG_WALL = 0xfbff, REG_MOUNT = 0xfdff, REG_FOREST = 0xfeff };

enum MISSILE {
	LIGHTNING = 0x00, GRIF_HAMMER = 0x01, DRAGON_BREATH = 0x02, MIS_FLAME_SHIELD = 0x03, BIG_CANNON = 0x07, TOUCH_O_DEATH = 0x0a,
	ROCK = 0x0d, BOLT = 0x0e, ARROW = 0x0f, AXE = 0x10, SUB_MISSLE = 0x11, TURTLE_MISSILE = 0x12,
	SMALL_CANNON = 0x18, DEMON_FIRE = 0x1b, NONE = 0x1d
};

enum UNIT_TYPE { GROUND, FLY, NAVAL };

enum SECOND_ACTION { ATTACK = 0x01, MOVE = 0x02, HARVEST = 0x03, HAUL_OIL = 0x04, DEMOLISH = 0x05, SAIL = 0x06 };

struct UnitsAllowed {
	int infantry_t1 : 1 {0}, //footman/grunt
		peon : 1 {0}, // or peasant
		artillery : 1 {0}, //balista/catapult
		infantry_t2 : 1 {0}, //knight, ogre
		ranged : 1 {0}, //axethrower/archer
		mystical : 1 {0}, //mage/death knight
		tanker : 1 {0},
		destroyer : 1 {0},
		transport : 1 {0},
		battleship : 1 {0},
		sub : 1 {0}, // or giant turtle
		scout : 1 {0}, // flying machine or zepplin
		flying : 1 {0}, //dragon/gryphon
		unused : 1 {0},
		kaboom : 1 {0}, //Sappers/demo squad
		roost : 1 {0}, //or aviary
		farm : 1 {0},
		barracks : 1 {0},
		mill : 1 {0},
		stables : 1 {0}, //or mound
		temple : 1 {0}, //or mage tower
		foundry : 1 {0},
		refinery : 1 {0},
		inventor : 1 {0}, //or alchemist
		church : 1 {0}, // or altar of storms
		tower : 1 {0},
		hall : 1 {0},
		keep : 1 {0}, //or stronghold
		castle : 1 {0}, //or fortress
		blacksmith : 1 {0},
		shipyard : 1 {0};
};

struct SpellsAllowed {
	int holy_vis : 1 {0},
		healing : 1 {0},
		unused1 : 1 {0},
		exorcism : 1 {0},
		flame_shield : 1 {0},
		fireball : 1 {0},
		slow : 1 {0},
		invis : 1 {0},
		polymorph : 1 {0},
		bliz : 1 {0},
		kilrogg : 1 {0},
		bloodlust : 1 {0},
		unused2 : 1 {0},
		raise_dead : 1 {0},
		death_coil : 1 {0},
		whirlwind : 1 {0},
		haste : 1 {0},
		unholy_armor : 1 {0},
		runes : 1 {0},
		death_decay : 1 {0};
};


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
	void loadUDTA();
	void loadUNIT();
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

inline std::string UnitName(const UNIT& unit) {
	switch (unit) {
	case INFANTRY:
		return "Infantry";
	case GRUNT:
		return "Grunt";
	case PEASANT:
		return "Peasant";
	case PEON:
		return "Peon";
	case BALLISTA:
		return "Ballista";
	case CATAPULT:
		return "Catapult";
	case KNIGHT:
		return "Knight";
	case OGRE:
		return "Ogre";
	case ARCHER:
		return "Archer";
	case AXETHROWER:
		return "Axethrower";
	case MAGE:
		return "Mage";
	case DEATHKNIGHT:
		return "Death Knight";
	case PALADIN:
		return "Paladin";
	case OGREMAGE:
		return "Ogremage";
	case DWARVES:
		return "Demolition Squad";
	case SAPPER:
		return "Goblin Sapper";
	case ATTK_PEASANT:
		return "Attack Peasant";
	case ATTK_PEON:
		return "Attack Peon";
	case RANGER:
		return "Ranger";
	case BERSERKER:
		return "Berserker";
	case ALLERIA:
		return "Alleria";
	case TERON:
		return "Teron";
	case KURDAN:
		return "Kurdan";
	case DENTARG:
		return "Dentarg";
	case KHADGAR:
		return "Khadgar";
	case GROM:
		return "Grom";
	case H_TANKER:
		return "Human Tanker";
	case O_TANKER:
		return "Orc Tanker";
	case H_TRANSPORT:
		return "Human Transport";
	case O_TRANSPORT:
		return "Orc Transport";
	case H_DESTROYER:
		return "Human Destroyer";
	case O_DESTROYER:
		return "Orc Destroyer";
	case BATTLESHIP:
		return "Battleship";
	case JUGGERNAUGHT:
		return "Juggernaught";
	case DEATHWING:
		return "Deathwing";
	case SUBMARINE:
		return "Submarine";
	case TURTLE:
		return "Giant Turtle";
	case FLYING_MACHINE:
		return "Flying Machine";
	case ZEPPLIN:
		return "Zepplin";
	case GRYPHON:
		return "Gryphon Rider";
	case DRAGON:
		return "Dragon";
	case TURALYON:
		return "Turalyon";
	case EYE_KILROGG:
		return "Eye of Kilrogg";
	case DANATH:
		return "Danath";
	case KNORGATH:
		return "Knorgath";
	case CHOGALL:
		return "Chogall";
	case LOTHAR:
		return "Lothar";
	case GULDAN:
		return "Guldan";
	case UTHER:
		return "Uther";
	case ZULJIN:
		return "Zuljin";
	case SKELETON:
		return "Skeleton";
	case DAEMON:
		return "Daemon";
	case CRITTER:
		return "Critter";
	case H_FARM:
		return "Human Farm";
	case O_FARM:
		return "Orc Farm";
	case H_BARRACKS:
		return "Human Barracks";
	case O_BARRACKS:
		return "Orc Barracks";
	case CHURCH:
		return "Church";
	case ALTAR:
		return "Altar of Storms";
	case H_SCOUT_TOWER:
		return "Human Scout Tower";
	case O_SCOUT_TOWER:
		return "Orc Scout Tower";
	case STABLE:
		return "Stables";
	case OGREMOUND:
		return "Ogremound";
	case O_HALL:
		return "Orc Hall";
	case H_MILL:
		return "Human Mill";
	case O_MILL:
		return "Orc Mill";
	case H_FOUNDRY:
		return "Human Foundry";
	case O_FOUNDRY:
		return "Orc Foundry";
	case MAGE_TOWER:
		return "Mage Tower";
	case TEMPLE_DAMNED:
		return "Temple of the Damned";
	case H_KEEP:
		return "Human Keep";
	case O_STRONGHOLD:
		return "Orc Stronghold";
	case H_CASTLE:
		return "Human Castle";
	case O_FORTRESS:
		return "Orc Fortress";
	case GOLD:
		return "Goldmine";
	case OIL:
		return "Oil";
	case H_START:
		return "Human Start";
	case O_START:
		return "Orc Start";
	case H_BLACKSMITH:
		return "Human Blacksmith";
	case O_BLACKSMITH:
		return "Orc Blacksmith";
	case INVENTOR:
		return "Gnomish Inventor";
	case ALCHEMIST:
		return "Alchemist";
	case AVIARY:
		return "Aviary";
	case ROOST:
		return "Roost";
	case H_SHIPYARD:
		return "Human Shipyard";
	case O_SHIPYARD:
		return "Orc Shipyard";
	case H_HALL:
		return "Human Hall";
	case H_OIL_WELL:
		return "Human Oil Well";
	case O_OIL_WELL:
		return "Orc Oil Well";
	case H_GUARD_TOWER:
		return "Human Guard Tower";
	case O_GUARD_TOWER:
		return "Orc Guard Tower";
	case H_CANNON_TOWER:
		return "Human Cannon Tower";
	case O_CANNON_TOWER:
		return "Orc Cannon Tower";
	case CIRCLE_POWER:
		return "Circle of Power";
	case PORTAL:
		return "Portal";
	case RUNESTONE:
		return "Runestone";
	case H_WALL:
		return "Human Wall";
	case O_WALL:
		return "Orc Wall";
	default:
		return "Unknown";

	}
}
