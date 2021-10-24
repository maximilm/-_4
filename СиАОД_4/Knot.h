#pragma once
struct Knot {
	Knot* left = nullptr;
	Knot* right = nullptr;
	int num;
	long numInFile;
	int size = 1;
};