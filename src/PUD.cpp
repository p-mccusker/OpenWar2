#include "PUD.h"

const std::string UnitName(const UNIT& unit);

void findSectionHeaders(PUD& pud, const char* buffer, const int& len) {
	std::string sect;
	sect.resize(4);
	int sectionLen = 0;
	bool newSection = true;
	for (auto i = pud.startAddr; i < len-4; i++){
		sect[0] = buffer[i];
		sect[1] = buffer[i + 1];
		sect[2] = buffer[i + 2];
		sect[3] = buffer[i + 3];

		for (auto& header : HEADERS) {
			if (sect == header) {
				fileSection section;
				section.title = sect;
				section.startPos = i + 4 ; //Begins w/ 4 bytes descrbing the size of the section
				section.endPos = (section.startPos) + *(int*)&buffer[i + 4]; //End pos: start of size byte + sectionSize

				newSection = true;
				std::cout << "Found: " << sect << '\n';
				std::cout << "Start Pos:" << section.startPos << '\n';
				std::cout << "End Pos:" << section.endPos << '\n';

				if (pud.sections.size() > 0) {
					//Get reference to last entered section and retroactivley add endPos
					auto& lastSection = pud.sections[pud.sections.size()-1];
					lastSection.endPos = i - 1;
					
					//lastSection.size = lastSection.endPos - lastSection.startPos;
				}
				
				if (sect == "UNIT") { //Last section, get length know when to stop
					
					pud.sections.push_back(section);
					return;
				}
				pud.sections.push_back(section);
			}
		}
	}
	//Get reference to last entered section and retroactivley add endPos and start
	auto& lastSection = pud.sections[pud.sections.size() - 1];
	lastSection.endPos = len-1;
	//lastSection.size = lastSection.endPos - lastSection.startPos;


}

fileSection& Get(std::vector<fileSection>& vec, std::string title){
	for (auto &sect : vec) {
		if (sect.title == title)
			return sect;
	}
	fileSection none;
	return none;
}

inline void copyArrSectionToVector(const char* src, std::vector<pud::byte> &dest, const int &start, const int &end){
	for (int i = start; i <= end; i++){
		dest.push_back(src[i]);
	}
}

void printHexVec(std::vector<pud::byte> arr, const int& start, const int& end) {
	for (int i = start; i <= end; i++) {
		std::cout << "0x" << std::setfill('0') << std::setw(2) << std::right << std::hex << (int)arr[i] << ' ';
		//std::cout << std::hex << (int)buffer[i] << ' ';
		if (i - start % 12 == 0) // 12 cols
			std::cout << '\n';
	}

	std::cout << std::dec << ' ';
}

//void toByte(std::vector<pud::byte>& buffer, int& startPos, pud::byte& dest) {
void toByte(pud::byte *buffer, int& startPos, pud::byte& dest) {
	dest = buffer[startPos];
	startPos += sizeof(pud::byte);
}

void toWord(std::vector<pud::byte>& buffer, int& startPos, pud::word& dest) {
	dest = (pud::word)&buffer[startPos];
	startPos += sizeof(pud::word);
}

void toInt(std::vector<pud::byte>& buffer, int& startPos, pud::int4& dest) {
	dest = (pud::int4)&buffer[startPos];
	startPos += sizeof(pud::int4);
}

void isMapStdSize(Map& map) {
	/// Determine if a map if standard size
	/// 32x32, 64x64, 96x96, 128x128
	/// Game makes map out of y size
	/// Max size of 128x128
	
	if (map.y == 32 ||
		map.y == 64 ||
		map.y == 96 ||
		map.y == 128)
		map.standardSize = true;
	else
		map.standardSize = false;
}

PUD::PUD()
{
	file = "";
	startAddr = NULL;
}

PUD::PUD(const std::string& f, uint64_t addr)
{
	file = f;
	startAddr = addr;
}

PUD::~PUD()
{

}

void PUD::Load()
{
	std::ifstream pudFile{ file, std::ios::binary | std::ios::in};

	if (pudFile.fail())
		throw FILE_NOT_FOUND{};
	
	size_t fileLen = 0;
	pudFile.seekg(0, pudFile.end);
	fileLen = pudFile.tellg();
	fileLen -= startAddr; //Set offset
	pudFile.seekg(startAddr, pudFile.beg);
	char *buffer = new char[fileLen];
	pudFile.read(buffer, fileLen); //fix, need to find where pud ends

	findSectionHeaders(*this, buffer, fileLen); //Bugged

	for (auto& section : sections) {
		//Copy contents of the buffer hold the entire file into the individual sections
		copyArrSectionToVector(buffer, section.data, section.startPos, section.endPos);
		//std::cout << section.title << ": " << section.data.size() <<"\n";
		/*
		//std::cout << "\nSection : " << section.title << '\n'
		//	<< "Start Position: " << section.startPos << '\n'
		//	<< "End Position: " << section.endPos << '\n';
			//<< "Size: " << section.size << '\n';

		for (auto i = 0; i <= section.data.size(); i++){
			if ((int)section.data[i].to_ulong() >= 65 && (int)section.data[i].to_ulong() <= 122)
				std::cout << "["  << buffer[i] << ']';
			else
				std::cout << "["  << (int)section.data[i].to_ulong() << ']';
			//std::cout << std::hex << (int)buffer[i] << ' ';
			if (i % 12 == 0) // 12 cols
				std::cout << '\n';
		}

		//printHex(&buffer[0], section.startPos, section.endPos);
		*/
	}

	int sectionPos = 0;
	int sectionLen = 0;
	fileSection currSection;

	////TYPE//////
	currSection = Get(sections, "TYPE");
	bytesToType(currSection.data.data(), sectionPos, sectionLen);
	std::cout << currSection.title << ": " << sectionLen;
	std::string name(8, 0);
	readFromArray(currSection.data, sectionPos, name, name.size());
	bytesToType(currSection.data.data(), sectionPos, mapType.mapNum[0]);
	bytesToType(currSection.data.data(), sectionPos, mapType.mapNum[1]);

	bytesToType(currSection.data.data(), sectionPos, mapType.unused[0]);

	bytesToType(currSection.data.data(), sectionPos, mapType.tag[0]);
	bytesToType(currSection.data.data(), sectionPos, mapType.tag[1]);
	bytesToType(currSection.data.data(), sectionPos, mapType.tag[2]);
	bytesToType(currSection.data.data(), sectionPos, mapType.tag[3]);

	//////////////

	/////VER//////
	sectionPos = 0;
	currSection = Get(sections, "VER ");
	bytesToType(currSection.data.data(), sectionPos, sectionLen);
	std::cout << '\n' << currSection.title << ": " << sectionLen << '\n';
	bytesToType(currSection.data.data(), sectionPos, ver);
	//////////////

	/////DESC//////
	sectionPos = 0;
	currSection = Get(sections, "DESC");
	bytesToType(currSection.data.data(), sectionPos, sectionLen);
	std::cout << currSection.title << ": " << sectionLen << '\n';
	desc.resize(32);
	readFromArray(currSection.data, sectionPos, desc, desc.size());
	///////////////

	/////OWRN//////
	sectionPos = 0;
	currSection = Get(sections, "OWNR");
	bytesToType(currSection.data.data(), sectionPos, sectionLen);
	std::cout << currSection.title << ": " << sectionLen << '\n';

	for (int i = 0; i < 16; i++) {
		Player player;
		bytesToType(currSection.data.data(), sectionPos, player.ownr);
		players[i] = player;
	}

	//////////////

	/////ERA //////
	sectionPos = 0;
	currSection = Get(sections, "ERA ");
	bytesToType(currSection.data.data(), sectionPos, sectionLen);
	std::cout << currSection.title << ": " << sectionLen << '\n';
	bytesToType(currSection.data.data(), sectionPos, terrain);
	//////////////

	/////ERAX//////
	sectionPos = 0;
	//currSection = Get(sections, "ERAX"); // Broke
	if (currSection.title == "ERAX") { // May not exist
		bytesToType(currSection.data.data(), sectionPos, sectionLen);
		std::cout << currSection.title << ": " << sectionLen << '\n';
		bytesToType(currSection.data.data(), sectionPos, terrain); // If preset in v1.33+, it will be used instead of ERA
	}
	//////////////

	/////DIM //////
	sectionPos = 0;
	currSection = Get(sections, "DIM ");
	bytesToType(currSection.data.data(), sectionPos, sectionLen);
	std::cout << currSection.title << ": " << sectionLen << '\n';
	//printHexVec(currSection.data, 0, currSection.size - 1);
	bytesToType(currSection.data.data(), sectionPos, map.x);
	std::cout << "pos: " << sectionPos << '\n';
	bytesToType(currSection.data.data(), sectionPos, map.y);
	//////////////

	/////UDTA//////
	sectionPos = 0;
	currSection = Get(sections, "UDTA");
	bytesToType(currSection.data.data(), sectionPos, sectionLen);
	std::cout << currSection.title << ": " << sectionLen << '\n';
	bytesToType(currSection.data.data(), sectionPos, defaultUnitData);
	int NUM_UNITS = unitData.size();

	/*
	for(int i = 0; i < udtaUnused.capacity(); i++){
		bytesToType(currSection.data, sectionPos, udtaUnused[i]);
	}
	for(int i = 0; i < unitData.count(); i++){
		bytesToType(currSection.data, sectionPos, unitData[i].sight);
	}
	for(int i = 0; i < unitData.count(); i++){
		bytesToType(currSection.data, sectionPos, unitData[i].hp);
	}
	for(int i = 0; i < unitData.count(); i++){
		bytesToType(currSection.data, sectionPos, unitData[i].gldCost);
	}
	for(int i = 0; i < unitData.count(); i++){
		bytesToType(currSection.data, sectionPos, unitData[i].lumbrCost);
	}
	for(int i = 0; i < unitData.count(); i++){
		bytesToType(currSection.data, sectionPos, unitData[i].oilCost);
	}
	for(int i = 0; i < unitData.count(); i++){
		bytesToType(currSection.data, sectionPos, unitData[i].unitSize);
	}
	for(int i = 0; i < unitData.count(); i++){
		bytesToType(currSection.data, sectionPos, unitData[i].boxSize);
	}
	for(int i = 0; i < unitData.count(); i++){
		bytesToType(currSection.data, sectionPos, unitData[i].atkRange);
	}
	for(int i = 0; i < unitData.count(); i++){
		bytesToType(currSection.data, sectionPos, unitData[i].reactRangeCmp);
	}
	for(int i = 0; i < unitData.count(); i++){
		bytesToType(currSection.data, sectionPos, unitData[i].reactRangePlyr);
	}
	for(int i = 0; i < unitData.count(); i++){
		bytesToType(currSection.data, sectionPos, unitData[i].armor);
	}
	for(int i = 0; i < unitData.count(); i++){
		bytesToType(currSection.data, sectionPos, unitData[i].selectable);
	}
	for(int i = 0; i < unitData.count(); i++){
		bytesToType(currSection.data, sectionPos, unitData[i].priority);
	}
	for(int i = 0; i < unitData.count(); i++){
		bytesToType(currSection.data, sectionPos, unitData[i].dmg_basic);
	}
	for(int i = 0; i < unitData.count(); i++){
		bytesToType(currSection.data, sectionPos, unitData[i].dmg_piercing);
	}
	for(int i = 0; i < unitData.count(); i++){
		bytesToType(currSection.data, sectionPos, unitData[i].weaponsUpgradable);
	}
	for(int i = 0; i < unitData.count(); i++){
		bytesToType(currSection.data, sectionPos, unitData[i].armorUpgradable);
	}
	for(int i = 0; i < unitData.count(); i++){
		bytesToType(currSection.data, sectionPos, unitData[i].missle);
	}
	for(int i = 0; i < unitData.count(); i++){
		bytesToType(currSection.data, sectionPos, unitData[i].type);
	}
	for(int i = 0; i < unitData.count(); i++){
		bytesToType(currSection.data, sectionPos, unitData[i].decayRate);
	}
	for(int i = 0; i < unitData.count(); i++){
		bytesToType(currSection.data, sectionPos, unitData[i].cmpAnnoyFactor);
	}
	for(int i = 0; i < 58; i++){ // Only first 58
		bytesToType(currSection.data, sectionPos, unitData[i].secondAction);
	}
	for(int i = 0; i < unitData.count(); i++){
		bytesToType(currSection.data, sectionPos, unitData[i].pntVal);
	}
	for(int i = 0; i < unitData.count(); i++){
		bytesToType(currSection.data, sectionPos, unitData[i].canTarget);
	}
	for(int i = 0; i < unitData.count(); i++){
		bytesToType(currSection.data, sectionPos, unitData[i].flags);
	}
	for(int i = 0; i < udtaSwampFrames.capacity(); i++){
		bytesToType(currSection.data, sectionPos, udtaSwampFrames[i]);
	}
	std::cout << "End pos: " << sectionPos << '\n';

	for (auto &unit : unitData){
		std::cout <<  unit.type << '\n';
	}*/

	for (int i = 0; i < NUM_UNITS; i++) {
		Unit newUnit;
		bytesToType(currSection.data.data(), sectionPos, newUnit.overlapFrame);
		unitData[i] = newUnit;
	}

	for (int i = 0; i < udtaUnused.size(); i++) {
		bytesToType(currSection.data.data(), sectionPos, udtaUnused[i]);
	}
	for (int i = 0; i < NUM_UNITS; i++) {
		bytesToType(currSection.data.data(), sectionPos, unitData[i].sight);
	}
	for (int i = 0; i < NUM_UNITS; i++) {
		bytesToType(currSection.data.data(), sectionPos, unitData[i].hp);
	}
	for (int i = 0; i < NUM_UNITS; i++) {
		bytesToType(currSection.data.data(), sectionPos, unitData[i].gldCost);
	}
	for (int i = 0; i < NUM_UNITS; i++) {
		bytesToType(currSection.data.data(), sectionPos, unitData[i].lumbrCost);
	}
	for (int i = 0; i < NUM_UNITS; i++) {
		bytesToType(currSection.data.data(), sectionPos, unitData[i].oilCost);
	}
	for (int i = 0; i < NUM_UNITS; i++) {
		bytesToType(currSection.data.data(), sectionPos, unitData[i].unitSize);
	}
	for (int i = 0; i < NUM_UNITS; i++) {
		bytesToType(currSection.data.data(), sectionPos, unitData[i].boxSize);
	}
	for (int i = 0; i < NUM_UNITS; i++) {
		bytesToType(currSection.data.data(), sectionPos, unitData[i].atkRange);
	}
	for (int i = 0; i < NUM_UNITS; i++) {
		bytesToType(currSection.data.data(), sectionPos, unitData[i].reactRangeCmp);
	}
	for (int i = 0; i < NUM_UNITS; i++) {
		bytesToType(currSection.data.data(), sectionPos, unitData[i].reactRangePlyr);
	}
	for (int i = 0; i < NUM_UNITS; i++) {
		bytesToType(currSection.data.data(), sectionPos, unitData[i].armor);
	}
	for (int i = 0; i < NUM_UNITS; i++) {
		bytesToType(currSection.data.data(), sectionPos, unitData[i].selectable);
	}
	for (int i = 0; i < NUM_UNITS; i++) {
		bytesToType(currSection.data.data(), sectionPos, unitData[i].priority);
	}
	for (int i = 0; i < NUM_UNITS; i++) {
		bytesToType(currSection.data.data(), sectionPos, unitData[i].dmg_basic);
	}
	for (int i = 0; i < NUM_UNITS; i++) {
		bytesToType(currSection.data.data(), sectionPos, unitData[i].dmg_piercing);
	}
	for (int i = 0; i < NUM_UNITS; i++) {
		bytesToType(currSection.data.data(), sectionPos, unitData[i].weaponsUpgradable);
	}
	for (int i = 0; i < NUM_UNITS; i++) {
		bytesToType(currSection.data.data(), sectionPos, unitData[i].armorUpgradable);
	}
	for (int i = 0; i < NUM_UNITS; i++) {
		bytesToType(currSection.data.data(), sectionPos, unitData[i].missle);
	}
	for (int i = 0; i < NUM_UNITS; i++) {
		bytesToType(currSection.data.data(), sectionPos, unitData[i].type);
	}
	for (int i = 0; i < NUM_UNITS; i++) {
		bytesToType(currSection.data.data(), sectionPos, unitData[i].decayRate);
	}
	for (int i = 0; i < NUM_UNITS; i++) {
		bytesToType(currSection.data.data(), sectionPos, unitData[i].cmpAnnoyFactor);
	}
	for (int i = 0; i < 58; i++) { // Only first 58
		bytesToType(currSection.data.data(), sectionPos, unitData[i].secondAction);
	}
	for (int i = 0; i < NUM_UNITS; i++) {
		bytesToType(currSection.data.data(), sectionPos, unitData[i].pntVal);
	}
	for (int i = 0; i < NUM_UNITS; i++) {
		bytesToType(currSection.data.data(), sectionPos, unitData[i].canTarget);
	}
	for (int i = 0; i < NUM_UNITS; i++) {
		bytesToType(currSection.data.data(), sectionPos, unitData[i].flags);
	}
	if (file == "data/gamedat/MAINDAT.WAR dfaf") {
		for (int i = 0; i < udtaSwampFrames.size(); i++) {
			bytesToType(currSection.data.data(), sectionPos, udtaSwampFrames[i]);
		}
	}

	for (int i = 0; i < units.size(); i++) {
		auto& unit = unitData[units[i]];
		unit.kind = units[i];
		unit.name = UnitName((UNIT)unit.kind);
	}

	//////////////

	/////ALOW//////
	sectionPos = 0;
	//currSection = Get(sections, "ALOW"); //Broke
	if (currSection.title == "ALOW") {
		bytesToType(currSection.data.data(), sectionPos, sectionLen);
		std::cout << currSection.title << ": " << sectionLen << '\n';
		for (int i = 0; i < 16; i++)
			bytesToType(currSection.data.data(), sectionPos, players[i].techTree.allowedUnitBld);
		for (int i = 0; i < 16; i++)
			bytesToType(currSection.data.data(), sectionPos, players[i].techTree.startSpells);
		for (int i = 0; i < 16; i++)
			bytesToType(currSection.data.data(), sectionPos, players[i].techTree.allowedSpells);
		for (int i = 0; i < 16; i++)
			bytesToType(currSection.data.data(), sectionPos, players[i].techTree.currSpellsUpgrading);
		for (int i = 0; i < 16; i++)
			bytesToType(currSection.data.data(), sectionPos, players[i].techTree.allowedUpgrade);
		for (int i = 0; i < 16; i++)
			bytesToType(currSection.data.data(), sectionPos, players[i].techTree.currUpgrading);
	}
	//////////////

	/////UGRD//////
	sectionPos = 0;																									
	currSection = Get(sections, "UGRD");
	bytesToType(currSection.data.data(), sectionPos, sectionLen);
	std::cout << currSection.title << ": " << sectionLen << '\n';
	bytesToType(currSection.data.data(), sectionPos, defaultUpgradeData);
	for (int i = 0; i < upgrades.size(); i++) {
		Upgrade newUp;
		bytesToType(currSection.data.data(), sectionPos, newUp.upgrdTime);
		upgrades[i] = newUp;
	}
	for (int i = 0; i < upgrades.size(); i++)
		bytesToType(currSection.data.data(), sectionPos, upgrades[i].gldCost);
	for (int i = 0; i < upgrades.size(); i++)
		bytesToType(currSection.data.data(), sectionPos, upgrades[i].lumbrCost);
	for (int i = 0; i < upgrades.size(); i++)
		bytesToType(currSection.data.data(), sectionPos, upgrades[i].oilCost);
	for (int i = 0; i < upgrades.size(); i++)
		bytesToType(currSection.data.data(), sectionPos, upgrades[i].upgrdIcon);
	for (int i = 0; i < upgrades.size(); i++)
		bytesToType(currSection.data.data(), sectionPos, upgrades[i].group);
	for (int i = 0; i < upgrades.size(); i++)
		bytesToType(currSection.data.data(), sectionPos, upgrades[i].affectFlags);
	//////////////

	/////SIDE//////
	sectionPos = 0;
	currSection = Get(sections, "SIDE");
	bytesToType(currSection.data.data(), sectionPos, sectionLen);
	std::cout << currSection.title << ": " << sectionLen << '\n';

	for (int i = 0; i < players.size(); i++)
		toByte(currSection.data.data(), sectionPos, players[i].race);
	
	///////////////

	/////SGLD//////
	sectionPos = 0;
	currSection = Get(sections, "SGLD");
	bytesToType(currSection.data.data(), sectionPos, sectionLen);
	std::cout << currSection.title << ": " << sectionLen << '\n';

	for (int i = 0; i < players.size(); i++)
		bytesToType(currSection.data.data(), sectionPos, players[i].sGold);
	///////////////

	/////SLBR//////
	sectionPos = 0;
	currSection = Get(sections, "SLBR");
	bytesToType(currSection.data.data(), sectionPos, sectionLen);
	std::cout << currSection.title << ": " << sectionLen << '\n';

	for (int i = 0; i < players.size(); i++)
		bytesToType(currSection.data.data(), sectionPos, players[i].sWood);
	///////////////

	/////SOIL//////
	sectionPos = 0;
	currSection = Get(sections, "SOIL");
	bytesToType(currSection.data.data(), sectionPos, sectionLen);
	std::cout << currSection.title << ": " << sectionLen << '\n';

	for (int i = 0; i < players.size(); i++)
		bytesToType(currSection.data.data(), sectionPos, players[i].sOil);
	///////////////

	/////AIPL//////
	sectionPos = 0;
	currSection = Get(sections, "AIPL");
	bytesToType(currSection.data.data(), sectionPos, sectionLen);
	std::cout << currSection.title << ": " << sectionLen << '\n';

	for (int i = 0; i < players.size(); i++)
		bytesToType(currSection.data.data(), sectionPos, players[i].ai);
	///////////////

	/////MTXM//////
	sectionPos = 0;
	currSection = Get(sections, "MTXM");
	bytesToType(currSection.data.data(), sectionPos, sectionLen);
	std::cout << currSection.title << ": " << sectionLen << '\n';

	for (int i = 0; i < map.x * map.y; i++) {
		pud::word tile;
		bytesToType(currSection.data.data(), sectionPos, tile);
		map.tilesMap.push_back(tile);
	}
	///////////////

	/////SQM //////
	sectionPos = 0;
	currSection = Get(sections, "SQM ");
	bytesToType(currSection.data.data(), sectionPos, sectionLen);
	std::cout << currSection.title << ": " << sectionLen << '\n';

	for (int i = 0; i < map.x * map.y; i++) {
		pud::word tile;
		bytesToType(currSection.data.data(), sectionPos, tile);
		map.actionMap.push_back(tile);
	}
	///////////////

	/////OILM//////
	sectionPos = 0;
	currSection = Get(sections, "OILM");
	bytesToType(currSection.data.data(), sectionPos, sectionLen);
	std::cout << currSection.title << ": " << sectionLen << '\n';

	for (int i = 0; i < map.x * map.y; i++) {
		pud::byte concentrationLevel;
		bytesToType(currSection.data.data(), sectionPos, concentrationLevel);
		oilConcentration.push_back(concentrationLevel);
	}
	///////////////

	/////UNIT//////
	sectionPos = 0;
	currSection = Get(sections, "UNIT");
	bytesToType(currSection.data.data(), sectionPos, sectionLen);
	std::cout << currSection.title << ": " << sectionLen << '\n';

	for (int i = 0; i < sectionLen / 8 * sizeof(pud::byte); i++) {
		pud::word x, y, gldOilOther;
		pud::byte kind, owner;

		Unit newUnit;
		bytesToType(currSection.data.data(), sectionPos, x);
		bytesToType(currSection.data.data(), sectionPos, y);
		bytesToType(currSection.data.data(), sectionPos, kind);
		for (auto& unit : unitData) {
			if (unit.kind == kind) {
				newUnit = unit;
			}
		}
		newUnit.xCoord = x;
		newUnit.yCoord = y;
		newUnit.kind = kind;

		bytesToType(currSection.data.data(), sectionPos, owner);
		bytesToType(currSection.data.data(), sectionPos, gldOilOther);
		newUnit.owner = owner;
		newUnit.capacity = gldOilOther;
		currentUnits.push_back(newUnit);
	}

	for (auto& unit : currentUnits) {
		std::cout << UnitName((UNIT)unit.kind) << '\n';
	}
	///////////////
}

void PUD::Save(const std::string& outFile)
{

}
