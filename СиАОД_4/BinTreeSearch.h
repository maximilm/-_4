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
	long srv = 0;
	void insert(Knot** k, int key, long numInFile);
	void createTree(Knot** root);
	void printTree(Knot** key, int level);
	void knotDelete(Knot** k, int key);
	Knot* find(Knot* root, int key);



	Knot* searchParent(Knot* root, Knot* key);
	void updateRoot();
	Knot** getRoot();
};

