#include "GenFile.h"
void genFile(int n) { // функция заполнения файла записями
	setlocale(LC_ALL, "russian");
	locale::global(locale(".utf8"));
	srand(time(0));
	ofstream fb;
	ofstream f;
	f.open("polisa.txt");
	fb.open("polisaBIN.dat", ios::binary);
	string cmp = genRandomLetter(4),surname = genRandomLetter(6), numInString = genRandomDigits(3);
	f << numInString << "/" << cmp << "/" << surname << "/";
	int num = atoi(numInString.c_str());
	Polis* p1 = new Polis(num, cmp, surname, 1);
	fb.write((char*)p1, sizeof(Polis));
	for (int i = 1; i < n; i++) {
		cmp = genRandomLetter(4);
		surname = genRandomLetter(6);
		numInString = genRandomDigits(3);
		insertInFile(f, fb, numInString, cmp, surname, i+1);
	}
	f.close();
	fb.close();
}
void genBINfile(int n) {
	ifstream f;
	ofstream fb;
	int num;
	fb.open("polisaBIN.dat", ios::binary);
	f.open("polisa.txt");
	int numberRecords = 0, j = 0;
	string stringInFile;
	string* del = new string[3]; // массив для трех строк - номер, компания, фамилия
	while (!f.eof()) {
		numberRecords++;
		getline(f, stringInFile);
		while (stringInFile.find("/") != -1)
		{
			del[j] = stringInFile.substr(0, stringInFile.find("/"));
			stringInFile.erase(0, stringInFile.find("/") + 1);
			j++;
		}
		num = atoi(del[0].c_str());
		Polis* p = new Polis(num, del[1], del[2], numberRecords);
		fb.write((char*)p, sizeof(Polis));
		j = 0;
	}
	f.close();
	fb.close();
}
void insertInFile(ofstream& f, ofstream& fb, string num, string cmp, string surname, int numInFile) {
	f << endl << num << "/" << cmp << "/" << surname << "/";
	int num2 = atoi(num.c_str());
	Polis* p1 = new Polis(num2, cmp, surname, numInFile);
	fb.write((char*)p1, sizeof(Polis));
}
string genRandomLetter(const int len) { // функция рандома для  ФИО студента 
	string tmp_s;
	static const char alphanum[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	tmp_s.reserve(len);
	for (int i = 0; i < len; ++i)
		tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
	return tmp_s;
}
string genRandomDigits(const int len) { // функция рандома для номер страхового полиса
	string tmp_s;
	static const char alphanum[] =
		"123456789";
	tmp_s.reserve(len);
	for (int i = 0; i < len; ++i)
		tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
	return tmp_s;
}
Polis findInFile(long numInFile) {
	ifstream bf("polisaBIN.dat", ios::in | ios::binary);
	Polis p2;
	bf.seekg((numInFile-1) * sizeof(Polis), ios::beg);
	bf.read((char*)&p2, sizeof(Polis));
	bf.close();
	return p2;
}

void deletePolisInBinTxt(long numInFile) {
	ifstream f1("Polisa.txt"); // чтение 
	ofstream f2("Help.txt"); // запись
	string q, q1;
	Polis itg = findInFile(numInFile);
	bool flag = false;
	q1 = itg.getNum() + "/" + itg.getKmp() + "/" + itg.getSurname() + "/"; // строка, которую нужно удалить 
	getline(f1, q); // строка из файла
	if (q != q1) 
		f2 << q;
	else 
		flag = true;
	while (!f1.eof())
	{
		getline(f1, q);
		if (q != q1) 
			if (flag) {
				f2 << q;
				flag = false;
			}
			else
				f2 << endl << q;
	}
	f1.close();
	f2.close();
	f1.open("Help.txt");
	f2.open("Polisa.txt");
	getline(f1, q);
	f2 << q;
	while (!f1.eof())
	{
		getline(f1, q);
		f2 << endl << q;
	}
	f1.close();
	f2.close();
}