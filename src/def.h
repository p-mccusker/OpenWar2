#ifndef DEF_H
#define DEF_H
#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <iomanip>
#include "Array.h"

//using u_byte = unsigned char;
namespace pud {
	using int4 = std::bitset<32>;
	using word = std::bitset<16>;
	using byte = unsigned char;

}
//Section Headers
const std::vector<std::string> HEADERS = {  "TYPE", "VER ", "DESC", "OWNR", "ERA ", "ERAX", "DIM ", "UDTA", "ALOW", "UGRD", "SIDE",
											"SGLD", "SLBR", "SOIL", "AIPL", "MTXM", "SQM ", "OILM", "REGM", "UNIT" };

enum VER_ { HEROES_NO = 0x11, HEROES_YES = 0x13 };

enum OWNR { PASSIVE_COMP_PLAYER = 0x02, NO_PLAYER = 0x03, COMP_PLAYER = 0x04, HUMAN_PLAYER = 0x05, RESCUE_PASSIVE = 0x06,
			RESCUE_ACTIVE = 0x07 };

enum ERA_ { FOREST_TYPE = 0x00, WINTER_TYPE = 0x01, WASTELAND_TYPE = 0x02, SWAMP_TYPE = 0x03};

enum SIDE {  HUMAN = 0x00, ORC = 0x01, NEUTRAL = 0x02 };

//Test for values
enum SGLD { P1_GOLD,  P2_GOLD,  P3_GOLD, P4_GOLD, P5_GOLD, P6_GOLD, P7_GOLD, P8_GOLD, P9_GOLD, P10_GOLD, P11_GOLD, P12_GOLD,
			P13_GOLD, P14_GOLD, P15_GOLD, P16_GOLD};

enum UNIT { INFANTRY = 0x00,		GRUNT = 0x01,				PEASANT = 0x02,			PEON = 0x03,			BALLISTA = 0x04,
			CATAPULT = 0x05,		KNIGHT = 0x06,
			OGRE = 0x07,			ARCHER = 0x08,				AXETHROWER = 0x09,		MAGE = 0x0a,			DEATHKNIGHT = 0x0b,
			PALADIN = 0x0c,			OGREMAGE = 0x0d,			DWARVES = 0x0e,			SAPPER = 0x0f,			ATTK_PEASANT = 0x10,
			ATTK_PEON = 0x11,		RANGER = 0x12,				BERSERKER = 0x13,		ALLERIA = 0x14,			TERON = 0x15,
			KURDAN = 0x16,			DENTARG = 0x17,				KHADGAR = 0x18,			GROM = 0x19,			H_TANKER = 0x1a,
			O_TANKER = 0x01b,		H_TRANSPORT = 0x1c,			O_TRANSPORT = 0x1d,		H_DESTROYER = 0x1e,		O_DESTROYER = 0x1f,
			BATTLESHIP = 0x20,		JUGGERNAUGHT = 0x21,		DEATHWING = 0x23,		SUBMARINE = 0x26,		TURTLE = 0x27,
			FLYING_MACHINE = 0x28,	ZEPPLIN = 0x29,				GRYPHON = 0x2a,			DRAGON = 0x2b,			TURALYON = 0x2c,
			EYE_KILROGG = 0x2d,		DANATH = 0x2e,				KNORGATH = 0x2f,		CHOGALL = 0x31,			LOTHAR = 0x32,
			GULDAN = 0x33,			UTHER = 0x34,				ZULJIN = 0x35,			SKELETON = 0x37,		DAEMON = 0x38,
			CRITTER = 0x39,			H_FARM = 0x3a,				O_FARM = 0x3b,			H_BARRACKS = 0x3c,		O_BARRACKS = 0x3d,
			CHURCH = 0x3e,			ALTAR = 0x3f,				H_SCOUT_TOWER = 0x40,	O_SCOUT_TOWER = 0x41,	STABLE = 0x42,
			OGREMOUND = 0x43,		INVENTOR = 0x44,			ALCHEMIST = 0x45,		AVIARY = 0x46,			ROOST = 0x47,
			H_SHIPYARD = 0x48,		O_SHIPYARD = 0x49,			H_HALL = 0x4a,			O_HALL = 0x4b,			H_MILL = 0x4c,
			O_MILL = 0x4d,			H_FOUNDRY = 0x4e,			O_FOUNDRY = 0x4f,		MAGE_TOWER = 0x50,		TEMPLE_DAMNED = 0x51,
			H_BLACKSMITH = 0x52,	O_BLACKSMITH = 0x53,		H_REFINERY = 0x54,		O_REFINERY = 0x55,		H_OIL_WELL = 0x56,
			O_OIL_WELL = 0x57,		H_KEEP = 0x58,				O_STRONGHOLD = 0x59,	H_CASTLE = 0x5a,		O_FORTRESS = 0x5b,
			GOLD = 0x5c,			OIL = 0x5d,					H_START = 0x5e,			O_START = 0x5f,			H_GUARD_TOWER = 0x60,
			O_GUARD_TOWER = 0x61,	H_CANNON_TOWER = 0x62,		O_CANNON_TOWER = 0x63,	CIRCLE_POWER = 0x64,	PORTAL = 0x65,
			RUNESTONE = 0x66,		H_WALL = 0x67,				O_WALL = 0x68,			NONE_UNIT };

const static std::vector<pud::word> units =
{	INFANTRY, GRUNT, PEASANT, PEON, BALLISTA, CATAPULT,	KNIGHT, OGRE, ARCHER, AXETHROWER, MAGE,	DEATHKNIGHT, PALADIN, OGREMAGE,
	DWARVES, SAPPER, ATTK_PEASANT, ATTK_PEON, RANGER, BERSERKER, ALLERIA, TERON, KURDAN, DENTARG, KHADGAR, GROM, H_TANKER, O_TANKER,
	H_TRANSPORT, O_TRANSPORT, H_DESTROYER, O_DESTROYER,	BATTLESHIP,	JUGGERNAUGHT, DEATHWING, SUBMARINE,	TURTLE,	FLYING_MACHINE,	ZEPPLIN,
	GRYPHON, DRAGON, TURALYON, EYE_KILROGG,	DANATH,	KNORGATH, CHOGALL, LOTHAR, GULDAN, UTHER, ZULJIN, SKELETON,	DAEMON,	CRITTER, H_FARM,
	O_FARM,	H_BARRACKS, O_BARRACKS,	CHURCH,	ALTAR, H_SCOUT_TOWER, O_SCOUT_TOWER, STABLE, OGREMOUND, INVENTOR, ALCHEMIST, AVIARY, ROOST,
	H_SHIPYARD, O_SHIPYARD,	H_HALL, O_HALL,	H_MILL,	O_MILL,	H_FOUNDRY, O_FOUNDRY, MAGE_TOWER, TEMPLE_DAMNED, H_BLACKSMITH, O_BLACKSMITH,
	H_REFINERY,	O_REFINERY,	H_OIL_WELL,	O_OIL_WELL,	H_KEEP, O_STRONGHOLD, H_CASTLE,	O_FORTRESS, GOLD, OIL, H_START,	O_START,
	H_GUARD_TOWER,	O_GUARD_TOWER, H_CANNON_TOWER, O_CANNON_TOWER, CIRCLE_POWER, PORTAL, RUNESTONE, H_WALL,	O_WALL
};


enum UGRD {	SW_1 = 0x00,				SW_2 = 0x01,				AXE_1 = 0x02,			AXE_2 = 0x03,			ARROW_1 = 0x04,
			ARROW_2 = 0x05,				SPEAR_1 = 0x06,				SPEAR_2 = 0x07,			H_SHIELD_1 = 0x08,		H_SHIELD_2 = 0x09,
			O_SHIELD_1 = 0x0a,			O_SHIELD_2 = 0x0b,			H_CANNON_1 = 0x0c,		H_CANNON_2 = 0x0d,		O_CANNON_1 = 0x0e,
			O_CANNON_2 = 0x0f,			H_SHIP_ARMOR_1 = 0x10,		H_SHIP_ARMOR_2 = 0x11,	O_SHIP_ARMOR_1 = 0x12,	O_SHIP_ARMOR_2 = 0x13,
			CATAPULT_1 = 0x14,			CATAPULT_2 = 0x15,			BALLISTA_1 = 0x16,		BALLISTA_2 = 0x17,		RANGERS = 0x18,
			LONGBOW = 0x19,				RANG_SCOUTING = 0x1a,		RANG_MARKS = 0x1b,		BESERKERS = 0x1c,		LIGHT_AXES = 0x1d,
			BERS_SCOUTING = 0x1e,		BERS_REGEN = 0x1f,			TRAIN_OGRE_MAGE = 0x20,	TRAIN_PALADIN = 0x21,	HOLY_VIS = 0x22,
			HEALING = 0x23,				EXOCISM = 0x24,				FLAME_SHIELD = 0x25,	FIREBALL = 0x26,		SLOW = 0x27,
			INVISIBILITY = 0x28,		POLYMORPH = 0x29,			BLIZZARD = 0x2a,		CAST_EYE_KILROGG = 0x2b,BLOODLUST = 0x2c,
			RAISE_DEAD = 0x2d,			DEATH_COIL = 0x2e,			WHIRLWIND = 0x2f,		HASTE = 0x30,			UNHOLY_ARMOR = 0x31,
			RUNES = 0x32,				DEATH_DECAY = 0x33 };

enum AIPL { AI_NEUT = 0x0, AI_0, AI_1, AI_2, AI_3, AI_4, AI_5, AI_6, AI_7,
			///*Unusable* AI
			AI_8, AI_9, AI_10, AI_11, AI_12, AI_13, AI_14, AI_15 };

enum MTXM {  };

enum SQM  { BRIDGE = 0x0000, LAND = 0x0001, COAST_CNR = 0x0002, DIRT = 0x0011, WATER = 0x0040, FOREST_MOUNT = 0x0081, COAST = 0x0082, WALLS = 0x008d,
			//0x0fxx		 //0x02xx
			SPACE = 0x0f00,  CAVE = 0x0200};

enum REGM { REG_WATER = 0x0000, REG_LAND = 0x4000, REG_ISLAND = 0xfaff, REG_WALL = 0xfbff, REG_MOUNT = 0xfdff, REG_FOREST = 0xfeff };

enum MISSILE { LIGHTNING = 0x00,      GRIF_HAMMER = 0x01, DRAGON_BREATH = 0x02,  MIS_FLAME_SHIELD = 0x03, BIG_CANNON = 0x07,  TOUCH_O_DEATH = 0x0a,
			   ROCK = 0x0d,           BOLT = 0x0e,        ARROW = 0x0f,          AXE = 0x10,              SUB_MISSLE = 0x11,  TURTLE_MISSILE = 0x12,
			   SMALL_CANNON = 0x18,   DEMON_FIRE = 0x1b,  NONE = 0x1d };

enum UNIT_TYPE { GROUND, FLY , NAVAL };

enum SECOND_ACTION { ATTACK = 0x01, MOVE= 0x02, HARVEST = 0x03, HAUL_OIL = 0x04, DEMOLISH = 0x05, SAIL = 0x06 };

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

struct SpellsAllowed{
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

//const std::string UnitName(const int& unit);



#endif // DEF_H
