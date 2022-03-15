#include "PUD.h"

using namespace std;

int main(int argc, char* argv[])
{
	//PUD reader("data/puds/ICEBRDGE.PUD", 0x0);
	//reader.Load();

	std::ifstream file { "data/images/14.rgb", std::ios::binary | std::ios::in };
	size_t fileLen = 0;
	file.seekg(0, file.end);
	fileLen = file.tellg();

	uint16_t* buffer = new uint16_t[fileLen / 2];
	file.read((char*)buffer, fileLen);
	std::cout << "Len: " << fileLen << '\n';

	for (int i = 0; i < fileLen; i++) {
		if (i % 24 == 0 && i > 0)
			std::cout << "|\n";
		std::string start = (i % 24 == 0) ? "| " : "";
		std::cout << start
				  << (uint16_t)buffer[i] << ' ';
	}
	return 0;
}
