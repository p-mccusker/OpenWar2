#include "pudreader.h"

std::string UnitName(const int& unit);

PUDReader::PUDReader(std::string file)
{
	_pud.fileName = file;

}

PUDReader::~PUDReader()
{

}

void PUDReader::Load()
{
	std::ifstream pudFile(_pud.fileName, std::istream::binary);

	if (!pudFile.fail()){
		pudFile.seekg(0, pudFile.end);
		int length = pudFile.tellg();
		pudFile.seekg(0, pudFile.beg);

		std::string buffer(length, 0);
		pudFile.read(&buffer[0],length);

		int sectionLen = 0;
		int pos = 0;
		std::string sectionTitle(4,0);
		//Type
		readFromArray(buffer, pos, sectionTitle, sectionTitle.size());
		bytesToType(buffer, pos, sectionLen);

		std::string mapNumStr(8,0);
		word mapNum;
		readFromArray(buffer, pos, mapNumStr, mapNumStr.size());
		bytesToType(buffer, pos, mapNum);

		_pud.mapNum = mapNum;

		word unused;
		bytesToType(buffer, pos, unused);

		int id = 0;
		bytesToType(buffer, pos, id);

		_pud.id = id;

		std::cout << "Section: " << sectionTitle << '\n';
		std::cout << "Section Length: " << sectionLen << '\n';
		std::cout << "Map: " << mapNum << '\n';
		std::cout << "ID: " << id << " \n";

		//VER
		readFromArray(buffer, pos, sectionTitle, sectionTitle.size());
		bytesToType(buffer, pos, sectionLen);

		word ver = 0;
		bytesToType(buffer, pos, ver);
		_pud.version = ver;

		std::cout << "\nSection: " << sectionTitle << '\n';
		std::cout << "Section Length: " << sectionLen << '\n';
		std::cout << "Version: " << ver << '\n';

		//DESC
		readFromArray(buffer, pos, sectionTitle, sectionTitle.size());
		bytesToType(buffer, pos, sectionLen);

		std::string desc(32,0);
		readFromArray(buffer, pos, desc, desc.size());
		_pud.desc = desc;

		std::cout << "\nSection: " << sectionTitle << '\n';
		std::cout << "Section Length: " << sectionLen << '\n';
		std::cout << "Description: " << desc << '\n';

		//OWNR
		readFromArray(buffer, pos, sectionTitle, sectionTitle.size());
		bytesToType(buffer, pos, sectionLen);

		//Read Controller for each player slot
		//0-7 Usable
		//8-14 Unusable
		//15 Neutral
		for (int i = 0; i < 16; i++){

			bytesToType(buffer, pos, _pud.playerSlots[i]);
		}

		std::cout << "\nSection: " << sectionTitle << '\n';
		std::cout << "Section Length: " << sectionLen << '\n';
		std::cout << "Controllers: ";
		for (int i = 0; i < 16; i++){
			std::cout << _pud.playerSlots[i] << ' ';
		}
		std::cout << '\n';

		//ERA
		readFromArray(buffer, pos, sectionTitle, sectionTitle.size());
		bytesToType(buffer, pos, sectionLen);

		word terrain;
		bytesToType(buffer, pos, terrain);
		_pud.terrain = terrain;

		std::cout << "\nSection: " << sectionTitle << '\n';
		std::cout << "Section Length: " << sectionLen << '\n';
		std::cout << "Terrain: " << std::hex << terrain << '\n';
		std::cout << std::dec;
		//ERAX ?? Not Implemented

		//DIM
		readFromArray(buffer, pos, sectionTitle, sectionTitle.size());
		bytesToType(buffer, pos, sectionLen);
		word x,y;
		bytesToType(buffer, pos, x);
		bytesToType(buffer, pos, y);

		_pud.width = x;
		_pud.height = y;

		std::cout << "\nSection: " << sectionTitle << '\n';
		std::cout << "Section Length: " << sectionLen << '\n';
		std::cout << "Map Width x Height: ( " << x << ',' << y << " )\n";

		//UDTA
		readFromArray(buffer, pos, sectionTitle, sectionTitle.size());
		bytesToType(buffer, pos, sectionLen);

		word isDefault;
		bytesToType(buffer, pos, isDefault);

		if (isDefault)
			_pud.isDefault = true;
		else
			_pud.isDefault = false;

		word overLapFrames;
		for (int i = 0; i < 110; i++){
			bytesToType(buffer, pos, overLapFrames);
			//if (contains(i, units)){

			//}
			Unit unit;
			unit.overlapFrames = overLapFrames;
			_pud.units.push_back(unit);

		}

		for (int i = 0; i < 508; i++){
			word temp;
			bytesToType(buffer, pos, temp);
			_pud.obsoleteFrameData.push_back(temp);
		}

		for (int i = 0; i < 110; i++){
			bytesToType(buffer, pos, _pud.units[i].sightRange);
		}
		for (int i = 0; i < 110; i++){
			bytesToType(buffer, pos, _pud.units[i].hp);
		}
		for (int i = 0; i < 110; i++){
			bytesToType(buffer, pos, _pud.units[i].magic);
		}
		for (int i = 0; i < 110; i++){
			bytesToType(buffer, pos, _pud.units[i].bldTime);
		}
		for (int i = 0; i < 110; i++){
			bytesToType(buffer, pos, _pud.units[i].gldCost);
		}
		for (int i = 0; i < 110; i++){
			bytesToType(buffer, pos, _pud.units[i].lmbrCost);
		}
		for (int i = 0; i < 110; i++){
			bytesToType(buffer, pos, _pud.units[i].oilCost);
		}
		for (int i = 0; i < 110; i++){
			bytesToType(buffer, pos, _pud.units[i].unitSize);
		}
		for (int i = 0; i < 110; i++){
			bytesToType(buffer, pos, _pud.units[i].boxSize);
		}
		for (int i = 0; i < 110; i++){
			bytesToType(buffer, pos, _pud.units[i].atkRange);
		}
		for (int i = 0; i < 110; i++){
			bytesToType(buffer, pos, _pud.units[i].compReactRange);
		}
		for (int i = 0; i < 110; i++){
			bytesToType(buffer, pos, _pud.units[i].humReactRange);
		}
		for (int i = 0; i < 110; i++){
			bytesToType(buffer, pos, _pud.units[i].armor);
		}
		for (int i = 0; i < 110; i++){
			bytesToType(buffer, pos, _pud.units[i].selectable);
		}
		for (int i = 0; i < 110; i++){
			bytesToType(buffer, pos, _pud.units[i].priority);
		}
		for (int i = 0; i < 110; i++){
			bytesToType(buffer, pos, _pud.units[i].basicDmg);
		}
		for (int i = 0; i < 110; i++){
			bytesToType(buffer, pos, _pud.units[i].pierceDmg);
		}
		for (int i = 0; i < 110; i++){
			bytesToType(buffer, pos, _pud.units[i].canUpWeapons);
		}
		for (int i = 0; i < 110; i++){
			bytesToType(buffer, pos, _pud.units[i].canUpArmor);
		}
		for (int i = 0; i < 110; i++){
			bytesToType(buffer, pos, _pud.units[i].missile);
		}
		for (int i = 0; i < 110; i++){
			bytesToType(buffer, pos, _pud.units[i].type);
		}
		for (int i = 0; i < 110; i++){
			bytesToType(buffer, pos, _pud.units[i].decayRate);
		}
		for (int i = 0; i < 110; i++){
			bytesToType(buffer, pos, _pud.units[i].annoyFactor);
		}
		for (int i = 0; i < 58; i++){
			bytesToType(buffer, pos, _pud.units[i].secondAction);
		}
		for (int i = 0; i < 110; i++){
			bytesToType(buffer, pos, _pud.units[i].pntVal);
		}
		for (int i = 0; i < 110; i++){
			bytesToType(buffer, pos, _pud.units[i].canTarget);
		}
		for (int i = 0; i < 110; i++){
			bytesToType(buffer, pos, _pud.units[i].flags);
		}
		for (int i = 0; i < 127; i++){
			word temp;
			bytesToType(buffer, pos, temp);
			_pud.obsoleteSwampFrame.push_back(temp);
		}







		std::cout << "\nSection: " << sectionTitle << '\n';
		std::cout << "Section Length: " << sectionLen << '\n';
		for (int i = 0; i < _pud.units.size(); i++){
			std::cout << "\nUnit: " << UnitName(i) << '\n';
			std::cout << "Unit hexcode: " << std::hex << i << '\n';
			std::cout << "HP: " << std::dec << _pud.units[i].hp << '\n';
			std::cout << "Gold: " << _pud.units[i].gldCost * 10 << '\n';
			std::cout << "Lumber: " << _pud.units[i].lmbrCost * 10 << '\n';
			std::cout << "Oil: " << _pud.units[i].oilCost * 10 << '\n';
		}


		//ALOW
		readFromArray(buffer, pos, sectionTitle, sectionTitle.size());
		bytesToType(buffer, pos, sectionLen);

		std::cout << "\nSection: " << sectionTitle << '\n';
		std::cout << "Section Length: " << sectionLen << '\n';

		//UGRD
		readFromArray(buffer, pos, sectionTitle, sectionTitle.size());
		bytesToType(buffer, pos, sectionLen);

		std::cout << "\nSection: " << sectionTitle << '\n';
		std::cout << "Section Length: " << sectionLen << '\n';

		//SIDE
		readFromArray(buffer, pos, sectionTitle, sectionTitle.size());
		bytesToType(buffer, pos, sectionLen);

		std::cout << "\nSection: " << sectionTitle << '\n';
		std::cout << "Section Length: " << sectionLen << '\n';

		//SGLD
		readFromArray(buffer, pos, sectionTitle, sectionTitle.size());
		bytesToType(buffer, pos, sectionLen);

		std::cout << "\nSection: " << sectionTitle << '\n';
		std::cout << "Section Length: " << sectionLen << '\n';

		//SLBR
		readFromArray(buffer, pos, sectionTitle, sectionTitle.size());
		bytesToType(buffer, pos, sectionLen);

		std::cout << "\nSection: " << sectionTitle << '\n';
		std::cout << "Section Length: " << sectionLen << '\n';

	}
	else
		std::cerr << "Error opening " << _pud.fileName << '\n';
}
