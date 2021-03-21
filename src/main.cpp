#include <iostream>

#include "pudreader.h"

using namespace std;

std::string UnitName(const int& unit){
	switch(unit){
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


int main(int argc, char* argv[])
{
	PUDReader reader("/home/peter/Games/warcraft_2/alamo.pud");
	reader.Load();


	return 0;
}
