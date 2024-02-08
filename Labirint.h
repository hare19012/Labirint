#ifndef LABIRINT_H
#define LABIRINT_H
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <fstream>
#include <set>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <windows.h>
using namespace std;

class Labirint{
    int brojRedova;
    int brojPozicija;
    vector<list<pair<int,pair<char,int>>>> lista_susjedstva;
    map<char, set<int>> prolazi;
    vector<int> put;
    bool provjeri(int,char);
    void kreirajListuSusjedstva();
    int vratiIndeks(char,int);
    bool provjeriIndeksZaPut(int);

public:
    Labirint();
    void ucitajIzFajla(const string&) ;
    int udaljenosti(char,int,char,int);
    void iscrtajPut();









};

#endif
