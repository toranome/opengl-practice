#pragma once

class Debug {
public:
	static void debugPrintArray(float* data, int arrayMemory);
	static void debugPrintArray(int* data, int arrayMemory);
private:
	template <typename T>
	static void debugPrintArrayGeneric(T* data, int arrayMemory);
};
