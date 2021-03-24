#include "PUD.h"

void findSectionHeaders(PUD& pud, const std::string& buffer) {
	int startPos = 0;

	for (int i = 0; i < buffer.size()-4; i++){
		std::string currsect = std::string((char)buffer[0] + (char)buffer[1] + (char)buffer[2] + (char)buffer[3]);
		if (contains(buffer[i+4]))
	}
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
	std::ifstream pudFile { _file };

	if (pudFile.fail())
		throw FILE_NOT_FOUND{};

	int fileLen = 0;
	pudFile.seekg(0, pudFile.end);
	fileLen = pudFile.tellg();
	pudFile.seekg(0, pudFile.beg);

	std::string buffer(fileLen, 0);
	pudFile.read(&buffer[0], fileLen);

	std::cout << buffer.size();


}

void PUD::Save()
{
}
