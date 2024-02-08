#include "Labirint.h"

int main(){
    try{
    Labirint a;
    a.ucitajIzFajla("fajl.txt");
    cout<<a.udaljenosti('L',30,'A',1);
    cout<<endl;
    cout<<endl;
    cout<<endl;
    a.iscrtajPut();


    }catch(const char *niz){
        cout<<niz;


    }
}
