#pragma once
#include "Knot.h"
#include "Polis.h"
#include "GenFile.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <random>
class RandomTreeSearch
{
private: 
	Knot* root = nullptr;
	int rotateCount = 0;
public:
	void createTree();
	Knot* getRoot();
	void setRoot(Knot* root);
	void printTree(Knot* key, int level);
	Knot* knotDelete(Knot* k, int key);
	Knot* find(Knot* root, int key);

	int getSize(Knot* k);
	void fixSize(Knot* k);
	Knot* rotateRight(Knot* k);
	Knot* rotateLeft(Knot* k);
	Knot* insertRoot(Knot* k, int key, long numInFile);
	Knot* insert(Knot* k, int key, long numInFile);

	Knot* join(Knot* small, Knot* big); // объединение двух деревьев
};

