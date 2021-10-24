#pragma once
#include "Knot.h"
#include "Polis.h"
#include "GenFile.h"
#include <iostream>
#include <fstream>
using namespace std;
class BinTreeSearch {
	Knot* root = nullptr;
public:
	void insert(Knot** k, int key, long numInFile);
	void createTree(Knot** root);
	Knot** getRoot();
	void printTree(Knot** key, int level);
	void knotDelete(Knot** k, int key);
	Knot* find(Knot* root, int key);
	Knot* searchParent(Knot* root, Knot* key);
	void updateRoot();
};

