#include "PUD.h"

void findSectionHeaders(PUD& pud, const std::string& buffer) {
	int startPos = 0;
	std::string sect;
	sect.resize(4);
	int sectionLen = 0;
	bool newSection = true;
	for (int i = 0; i < buffer.size()-4; i++){
		sect[0] = buffer[i];
		sect[1] = buffer[i + 1];
		sect[2] = buffer[i + 2];
		sect[3] = buffer[i + 3];

		for (auto& header : HEADERS) {
			if (sect == header) {
				fileSection section;
				section.title = sect;
				section.startPos = i + 4;
				newSection = true;

				if (pud.sections.size() > 0) {
					//Get reference to last entered section and retroactivley add endPos and start
					auto& lastSection = pud.sections[pud.sections.size()-1];
					lastSection.endPos = i - 1;
					lastSection.size = lastSection.endPos - lastSection.startPos;
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
	lastSection.size = lastSection.endPos - lastSection.startPos;
}

PUD::PUD()
{
	_file = "";
}

PUD::PUD(const std::string& file)
{
	_file = file;
}

PUD::~PUD()
{

}

void PUD::Load()
{
	std::ifstream pudFile { _file, std::ios::binary };

	if (pudFile.fail())
		throw FILE_NOT_FOUND{};

	int fileLen = 0;
	pudFile.seekg(0, pudFile.end);
	fileLen = pudFile.tellg();
	pudFile.seekg(0, pudFile.beg);
	std::string buffer(fileLen, 0);
	pudFile.read(&buffer[0], fileLen);

	std::cout << buffer.size() << std::endl;

	findSectionHeaders(*this, buffer); //Bugged



	for (auto section : sections) {
		std::cout << "\nSection : " << section.title << '\n'
			<< "Start Position: " << section.startPos << '\n'
			<< "End Position: " << section.endPos << '\n'
			<< "Size: " << section.size << '\n';

		//printHex(&buffer[0], section.startPos, section.endPos);

		for (int i = section.startPos; i <= section.endPos; i++){
			if ((int)buffer[i] >= 65 && (int)buffer[i] <= 122)
				std::cout << "["  << buffer[i] << ']';
			else
				std::cout << "["  << (int)buffer[i] << ']';
			//std::cout << std::hex << (int)buffer[i] << ' ';
			if (i - section.startPos % 12 == 0) // 12 cols
				std::cout << '\n';
		}

		std::cout << std::dec << ' ';

	}

}

void PUD::Save()
{
}
