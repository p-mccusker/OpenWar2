#include "PUD.h"

const std::string UnitName(const UNIT& unit);

void findSectionHeaders(PUD& pud, const std::string& buffer) {
	std::string sect;
	sect.resize(4);
	int sectionLen = 0;
	bool newSection = true;
	for (auto i = 0; i < buffer.size()-4; i++){
		sect[0] = buffer[i];
		sect[1] = buffer[i + 1];
		sect[2] = buffer[i + 2];
		sect[3] = buffer[i + 3];

		for (auto& header : HEADERS) {
			if (sect == header) {
				fileSection section;
				section.title = sect;
				section.startPos = i + 4 ;
				newSection = true;

				if (pud.sections.size() > 0) {
					//Get reference to last entered section and retroactivley add endPos and start
					auto& lastSection = pud.sections[pud.sections.size()-1];
					lastSection.endPos = i - 1;
					//lastSection.size = lastSection.endPos - lastSection.startPos;
				}
				pud.sections.push_back(section);

			}
		}

		if (newSection) {
			sectionLen = 0;
			newSection = false;
		}
		else
			sectionLen++;
	}
	//Get reference to last entered section and retroactivley add endPos and start
	auto& lastSection = pud.sections[pud.sections.size() - 1];
	lastSection.endPos =  buffer.size()-1;
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

void copyArrSectionToVector(const char* src, std::vector<pud::byte> &dest, const int &start, const int &end){
	for (int i = start; i <= end; i++){
		dest.push_back(src[i]);
	}
}

PUD::PUD()
{
	file = "";
}

PUD::PUD(const std::string& f)
{
	file = f;
}

PUD::~PUD()
{

}

void PUD::Load()
{
	std::ifstream pudFile { file, std::ios::binary };

	if (pudFile.fail())
		throw FILE_NOT_FOUND{};

	int fileLen = 0;
	pudFile.seekg(0, pudFile.end);
	fileLen = pudFile.tellg();
	pudFile.seekg(0, pudFile.beg);
	std::string buffer(fileLen, 0);
	pudFile.read(&buffer[0], fileLen);

	findSectionHeaders(*this, buffer); //Bugged

	for (auto &section : sections) {
		copyArrSectionToVector(&buffer[0], section.data, section.startPos, section.endPos);
		std::cout << section.title << '\n';
		//std::cout << "\nSection : " << section.title << '\n'
		//	<< "Start Position: " << section.startPos << '\n'
		//	<< "End Position: " << section.endPos << '\n';
			//<< "Size: " << section.size << '\n';
/*
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
	bytesToType(currSection.data, sectionPos, sectionLen);
	std::cout << currSection.title << ": " << sectionLen;
	std::string name(8,0);
	readFromArray(currSection.data, sectionPos, name, name.size());
	bytesToType(currSection.data, sectionPos, mapType.mapNum[0]);
	bytesToType(currSection.data, sectionPos, mapType.mapNum[1]);

	bytesToType(currSection.data, sectionPos, mapType.unused[0]);
	bytesToType(currSection.data, sectionPos, mapType.unused[1]);

	bytesToType(currSection.data, sectionPos, mapType.tag[0]);
	bytesToType(currSection.data, sectionPos, mapType.tag[1]);
	bytesToType(currSection.data, sectionPos, mapType.tag[2]);
	bytesToType(currSection.data, sectionPos, mapType.tag[3]);

	//////////////

	/////VER//////
	sectionPos = 0;
	currSection = Get(sections, "VER ");
	bytesToType(currSection.data, sectionPos, sectionLen);
	std::cout << '\n' << currSection.title << ": " << sectionLen << '\n';
	bytesToType(currSection.data, sectionPos, ver);
	//////////////

	/////DESC//////
	sectionPos = 0;
	currSection = Get(sections, "DESC");
	bytesToType(currSection.data, sectionPos, sectionLen);
	std::cout << currSection.title << ": " << sectionLen << '\n';
	desc.resize(32);
	readFromArray(currSection.data, sectionPos, desc, desc.size());
	///////////////

	/////OWRN//////
	sectionPos = 0;
	currSection = Get(sections, "OWNR");
	bytesToType(currSection.data, sectionPos, sectionLen);
	std::cout << currSection.title << ": " << sectionLen << '\n';

	for (int i = 0 ; i < 16; i++){
		Player player;
		bytesToType(currSection.data, sectionPos, player.owner);
		players[i] = player;
	}

	//////////////

	/////ERA //////
	sectionPos = 0;
	currSection = Get(sections, "ERA ");
	bytesToType(currSection.data, sectionPos, sectionLen);
	std::cout << currSection.title << ": " << sectionLen << '\n';
	bytesToType(currSection.data, sectionPos, terrain);
	//////////////

	/////ERAX//////
	sectionPos = 0;
	//currSection = Get(sections, "ERAX"); // Broke
	if (currSection.title == "ERAX"){ // May not exist
		bytesToType(currSection.data, sectionPos, sectionLen);
		std::cout << currSection.title << ": " << sectionLen << '\n';
		bytesToType(currSection.data, sectionPos, terrain); // If preset in v1.33+, it will be used instead of ERA
	}
	//////////////

	/////DIM //////
	sectionPos = 0;
	currSection = Get(sections, "DIM ");
	bytesToType(currSection.data, sectionPos, sectionLen);
	std::cout << currSection.title << ": " << sectionLen << '\n';
	bytesToType(currSection.data, sectionPos, map.x);
	bytesToType(currSection.data, sectionPos, map.y);
	//////////////

	/////UDTA//////
	sectionPos = 0;
	currSection = Get(sections, "UDTA");
	bytesToType(currSection.data, sectionPos, sectionLen);
	std::cout << currSection.title << ": " << sectionLen << '\n';
	bytesToType(currSection.data, sectionPos, defaultUnitData);
	int NUM_UNITS = 110;
	int cnt = 0;
	for (auto unit : units){
		Unit newUnit;
		newUnit.kind = (UNIT)unit.to_ulong();
		unitData[cnt] = newUnit;
		cnt++;
	}

	for(int i = 0; i < unitData.capacity(); i++){
		Unit newUnit;
		bytesToType(currSection.data, sectionPos, newUnit.overlapFrame);
		unitData[i] = newUnit;
	}

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
	}
	/*
	for(int i = 0; i < NUM_UNITS; i++){
		Unit newUnit;
		bytesToType(currSection.data, sectionPos, newUnit.overlapFrame);
		unitData[i] = newUnit;
	}

	for(int i = 0; i < udtaUnused.capacity(); i++){
		bytesToType(currSection.data, sectionPos, udtaUnused[i]);
	}
	for(int i = 0; i < NUM_UNITS; i++){
		bytesToType(currSection.data, sectionPos, unitData[i].sight);
	}
	for(int i = 0; i < NUM_UNITS; i++){
		bytesToType(currSection.data, sectionPos, unitData[i].hp);
	}
	for(int i = 0; i < NUM_UNITS; i++){
		bytesToType(currSection.data, sectionPos, unitData[i].gldCost);
	}
	for(int i = 0; i < NUM_UNITS; i++){
		bytesToType(currSection.data, sectionPos, unitData[i].lumbrCost);
	}
	for(int i = 0; i < NUM_UNITS; i++){
		bytesToType(currSection.data, sectionPos, unitData[i].oilCost);
	}
	for(int i = 0; i < NUM_UNITS; i++){
		bytesToType(currSection.data, sectionPos, unitData[i].unitSize);
	}
	for(int i = 0; i < NUM_UNITS; i++){
		bytesToType(currSection.data, sectionPos, unitData[i].boxSize);
	}
	for(int i = 0; i < NUM_UNITS; i++){
		bytesToType(currSection.data, sectionPos, unitData[i].atkRange);
	}
	for(int i = 0; i < NUM_UNITS; i++){
		bytesToType(currSection.data, sectionPos, unitData[i].reactRangeCmp);
	}
	for(int i = 0; i < NUM_UNITS; i++){
		bytesToType(currSection.data, sectionPos, unitData[i].reactRangePlyr);
	}
	for(int i = 0; i < NUM_UNITS; i++){
		bytesToType(currSection.data, sectionPos, unitData[i].armor);
	}
	for(int i = 0; i < NUM_UNITS; i++){
		bytesToType(currSection.data, sectionPos, unitData[i].selectable);
	}
	for(int i = 0; i < NUM_UNITS; i++){
		bytesToType(currSection.data, sectionPos, unitData[i].priority);
	}
	for(int i = 0; i < NUM_UNITS; i++){
		bytesToType(currSection.data, sectionPos, unitData[i].dmg_basic);
	}
	for(int i = 0; i < NUM_UNITS; i++){
		bytesToType(currSection.data, sectionPos, unitData[i].dmg_piercing);
	}
	for(int i = 0; i < NUM_UNITS; i++){
		bytesToType(currSection.data, sectionPos, unitData[i].weaponsUpgradable);
	}
	for(int i = 0; i < NUM_UNITS; i++){
		bytesToType(currSection.data, sectionPos, unitData[i].armorUpgradable);
	}
	for(int i = 0; i < NUM_UNITS; i++){
		bytesToType(currSection.data, sectionPos, unitData[i].missle);
	}
	for(int i = 0; i < NUM_UNITS; i++){
		bytesToType(currSection.data, sectionPos, unitData[i].type);
	}
	for(int i = 0; i < NUM_UNITS; i++){
		bytesToType(currSection.data, sectionPos, unitData[i].decayRate);
	}
	for(int i = 0; i < NUM_UNITS; i++){
		bytesToType(currSection.data, sectionPos, unitData[i].cmpAnnoyFactor);
	}
	for(int i = 0; i < 58; i++){ // Only first 58
		bytesToType(currSection.data, sectionPos, unitData[i].secondAction);
	}
	for(int i = 0; i < NUM_UNITS; i++){
		bytesToType(currSection.data, sectionPos, unitData[i].pntVal);
	}
	for(int i = 0; i < NUM_UNITS; i++){
		bytesToType(currSection.data, sectionPos, unitData[i].canTarget);
	}
	for(int i = 0; i < NUM_UNITS; i++){
		bytesToType(currSection.data, sectionPos, unitData[i].flags);
	}
	for(int i = 0; i < udtaSwampFrames.capacity(); i++){
		bytesToType(currSection.data, sectionPos, udtaSwampFrames[i]);
	}
	std::cout << "End pos: " << sectionPos << '\n';

	for (auto &unit : unitData){
		std::cout <<  UnitName(unit.type) <<
	}*/

	//////////////





}

void PUD::Save(const std::string& outFile)
{

}
