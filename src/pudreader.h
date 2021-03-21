#ifndef PUDREADER_H
#define PUDREADER_H

#include "def.h"

template<typename S, typename T>
bool contains(const S& item, const T& container){
	for (auto& it : container){
		if (it == item)
			return true;
	}
	return false;
}

template <typename T>
void readFromArray(const T& src, int &startPos, T& dest, const int& cnt){
	for (int i = 0; i < cnt; i++){
		dest[i] = src[startPos + i];
	}
	startPos += cnt;
}

template <typename T>
void bytesToType(std::string& buffer, int &startPos, T& dest){
	dest = *(T*)&buffer[startPos];
	startPos += sizeof(T);
}

class PUDReader
{
public:
	PUDReader(std::string file);
	~PUDReader();

	void Load();

private:
	PUD _pud;


};

#endif // PUDREADER_H
