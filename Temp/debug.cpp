#include "stdafx.h"
#include "Debug.h"

void Debug::debugPrintArray(float* data, int arrayMemory) {
	Debug::debugPrintArrayGeneric(data, arrayMemory);
}

void Debug::debugPrintArray(int* data, int arrayMemory) {
	Debug::debugPrintArrayGeneric(data, arrayMemory);
}

template <typename T>
void Debug::debugPrintArrayGeneric(T* data, int arrayMemory) {
	int size = arrayMemory / sizeof(T);
	std::cout << "Array [" << size << "] { ";
	for (int i = 0; i < size; i++)
	{
		std::cout << data[i];
		if (i != size - 1) {
			std::cout << ", ";
		}
	}
	std::cout << " }\n";
}