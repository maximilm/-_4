#pragma once
#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>
#include "Polis.h"
using namespace std;

	void genFile(int n);
	string genRandomDigits(const int len);
	string genRandomLetter(const int len);
	Polis findInFile(long numInFile);
	void insertInFile(ofstream& f, ofstream& fb, string num, string cmp, string surname, int numInFile);
	void deletePolisInBinTxt(long numInFile);
