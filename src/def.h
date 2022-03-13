#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <iomanip>
#include <array>

//using u_byte = unsigned char;
namespace pud {
	using int4 = uint32_t;
	using word = uint16_t;
	using byte = uint8_t;
}

template<typename S, typename T>
bool contains(const S& item, const T& container) {
	for (auto& it : container) {
		if (it == item)
			return true;
	}
	return false;
}

template <typename T>
void readFromArray(pud::byte* src, int& startPos, T& dest, const int& cnt) {
	for (int i = 0; i < cnt; i++) {
		dest[i] = src[startPos + i];
	}
	startPos += cnt;
}

template <typename T>
void bytesToType(pud::byte* buffer, int& startPos, T& dest) {
	dest = *static_cast<T*>(static_cast<void*>(&buffer[startPos]));
	startPos += sizeof(T);
}

template <typename T>
void printHex(const T arr[], const int& start, const int& end) {
	for (int i = start; i <= end; i++) {
		std::cout << "0x" << std::setfill('0') << std::setw(2) << std::right << std::hex << static_cast<int>(static_cast<void*>(&arr[i])) << ' ';
		//std::cout << std::hex << (int)buffer[i] << ' ';
		if (i - start % 12 == 0) // 12 cols
			std::cout << '\n';
	}

	std::cout << std::dec << ' ';
}

