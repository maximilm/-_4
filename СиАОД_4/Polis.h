#pragma once
#include <iostream>
#include <string>
using namespace std;
class Polis {
private:
	int num;
	char* kmp;
	char* surname;
	long numInFile;
public:
	Polis(int num, string kmp, string surname, long numInFile) {
		this->num = num;
		this->kmp = new char[4]{ kmp[0],kmp[1],kmp[2],kmp[3] };
		this->surname = new char[6]{ surname[0],surname[1],surname[2],surname[3],surname[4],surname[5]};
		this->numInFile = numInFile;
	}
	Polis() {
	}
	string getNum() {
		return to_string(num);
	}
	long getNumInFile() {
		return numInFile;
	}
	string getKmp() {
		string k = "";
		for (int i = 0; i < 4; i++)
			k = k + kmp[i];
		return k;
	}
	string getSurname() {
		string k = "";
		for (int i = 0; i < 6; i++)
			k = k + surname[i];
		return k;
	}
	void setNumInFile(int num) {
		this->num = num;
	}
	void setNum(int num) {
		this->num = num;
	}
	void setKmp(string newKmp) {
		for (int i = 0; i < 4; i++)
			kmp[i] = newKmp[i];
	}
	void setSurname(string newSurname) {
		for (int i = 0; i < 6; i++)
			surname[i] = newSurname[i];
	}
};