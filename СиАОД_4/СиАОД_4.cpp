#include <iostream>
#include <fstream>
#include "Polis.h"

#include "GenFile.h"
#include "BinTreeSearch.h"
#include "RandomTreeSearch.h"
using namespace std;
void menu_1(int capacity) {
    BinTreeSearch tree;
    int com, key, num2;
    Knot* findKnot;
    Polis p2;
    string kmp, surname, num;
    ofstream f;
    ofstream fb;
    setlocale(0, "ru");
    tree.createTree(tree.getRoot());
    cout <<  "1 - Добавить элемент в бинарное дерево;";
    cout << endl << "2 - Поиск ключа в дереве;";
    cout << endl << "3   Удаление ключа из дерева;";
    cout << endl << "4 - Вывод дерева в консоль;";
    cout << endl << "0 - Закончить работу программы.";
    do {
        cout << endl << "Введите номер функции: ";
        cin >> com;
        switch (com)
        {
        case 1:
            cout << "Введите последовательно: номер полиса(3 символа), название компании(4 символа), Фамилию владельца(6 символов): \n";
            cin >> num >> kmp >> surname;
            f.open("polisa.txt", ios::app);
            fb.open("polisaBIN.dat", ios::in | ios::binary | ios::app);
            insertInFile(f, fb, num, kmp, surname, ++capacity);
            num2 = atoi(num.c_str());
            tree.insert(tree.getRoot(), num2,capacity);
            f.close();
            fb.close();
            break;
        case 2:
            cout << "Введите ключ: ";
            cin >> key;
            findKnot = tree.find(*tree.getRoot(), key);
            if (findKnot != nullptr) {
                p2 = findInFile((*findKnot).numInFile);
                cout << "Найденный полис: " << endl;
                cout << "Номер полиса: " << p2.getNum() << endl
                    << "Название компании: " << p2.getKmp() << endl
                    << "Фамилия владельца: " << p2.getSurname() << endl
                    << "Номер записи в файле: " << p2.getNumInFile();
            }
            else
                cout << "Не найдено.";
            break;
        case 3:
            cout << "Введите ключ: ";
            cin >> key;
            if (tree.find(*tree.getRoot(),key) == nullptr)
                cout << "Такого узла нет.";
            else
                tree.knotDelete(tree.getRoot(), key);
            break;
        case 4:
            tree.printTree(tree.getRoot(), 0);
            break;
        }
    } while (com != 0);
}
void menu_2(int capacity) {
    RandomTreeSearch tree;
    int com,key, num2;
    Knot* findKnot;
    Polis p2;
    string kmp, surname, num;
    ofstream f;
    ofstream fb;
    setlocale(0, "ru");
    tree.createTree();
    cout << endl  << "1 - Добавить элемент в бинарное дерево;";
    cout << endl << "2 - Поиск ключа в дереве;";
    cout << endl << "3   Удаление ключа из дерева;";
    cout << endl << "4 - Вывод дерева в консоль;";
    cout << endl << "0 - Закончить работу программы.";
    
}
int main()
{
    setlocale(0, "ru");
    int capacity;
    cout << "Введите количество записей в бинарном файле: ";
    cin >> capacity;
    if (capacity == 0)
    {
        cout << "В файле должно быть больше чем 0 записей.";
        return 1;
    }
    genFile(capacity);
    int zadanie;
    setlocale(0, "");
    cout << "Введите номер задания(1 - бинарное дерево поиска, 2 - рандомизированное сбалансированное бинарное дерево поиска): ";
    cin >> zadanie;
    switch (zadanie)
    {
    case 1:
        menu_1(capacity);
        break;
    case 2:
        menu_2(capacity);
        break;
    }
    return 0;
}
