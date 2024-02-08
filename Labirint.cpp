#include "Labirint.h"
Labirint::Labirint(){
    brojPozicija=0;
    brojRedova=0;

}

void Labirint::ucitajIzFajla(const std::string& putanjaFajla) {
    ifstream fajl(putanjaFajla);
    string linija;
    if (fajl.is_open()) {
        // Učitavanje broja redova i pozicija
        getline(fajl, linija);
        brojRedova = stoi(linija);
        if(brojRedova%2!=0 || brojRedova>26) throw "Pogresno zapisan fajl!";
        getline(fajl, linija);
        brojPozicija = stoi(linija);

        // Učitavanje prolaza
        char red = 'B'; // Počinjemo od reda B
        while (getline(fajl, linija) && red <= 'Z') {
            istringstream iss(linija);
            int prolaz;
            char zarez;
            bool imaProlaza = false;
            while (iss >> prolaz) {

                prolazi[red].insert(prolaz);
                prolazi[red+1].insert(prolaz);
                if (iss.peek() == ',')
                    iss.ignore();
                imaProlaza = true;
            }

            // Dodajemo prolaze samo ako ih ima za taj red
            if (imaProlaza) {
                if (red < 'Z') red += 2; // Prelazimo na sledeći par redova

            } else {
                // Preskačemo redove bez prolaza
                break;
            }
        }


        fajl.close();
        kreirajListuSusjedstva();

    } else {
        cerr << "Ne mogu da otvorim fajl: " << putanjaFajla << endl;
    }




}
 bool Labirint::provjeri(int vrijednost, char red1) {
        // Provjeravamo postoji li ključ 'red1' u mapi
        auto it = prolazi.find(red1);
        if (it != prolazi.end()) {
            // Ako postoji, provjeravamo postoji li vrijednost 'a' u setu
            const std::set<int>& set = it->second;
            if (set.find(vrijednost) != set.end()) {
                // Ako postoji, vraćamo true
                return true;
            }
        }
        // Ako ne postoji, vraćamo false
        return false;
    }
void Labirint::kreirajListuSusjedstva(){
    lista_susjedstva.resize(brojPozicija*(brojRedova*2));
    bool provjera = false;
    char red = 'A';
    int brojac = 1;
    int brojPozicija2 = 0;
    for(int i(1);i<(brojRedova*2);i++){
        int brojac2 = 1;
        brojPozicija2 += brojPozicija;
        for(int j(brojPozicija2);j<(brojPozicija2+brojPozicija);j++){
            if(!provjera){
                if(brojac == 1){
                    lista_susjedstva[j-brojPozicija].push_back({j,{red,brojac2}});
                    lista_susjedstva[j].push_back({j-brojPozicija,{' ',brojac2}});
                    if(brojac2>1){
                        lista_susjedstva[j-1].push_back({j,{' ',brojac2}});
                        lista_susjedstva[j].push_back({j-1,{' ',brojac2}});
                    }
                    if(brojac2==brojPozicija){
                        brojac=2;
                    }

                }
                else if(brojac==2){
                    lista_susjedstva[j].push_back({j-brojPozicija,{' ',brojac2}});
                    lista_susjedstva[j-brojPozicija].push_back({j,{' ',brojac2}});
                    if(brojac2>1){
                        lista_susjedstva[j-1].push_back({j,{' ',brojac2}});
                        lista_susjedstva[j].push_back({j-1,{' ',brojac2}});
                    }
                    if(brojac2==brojPozicija){
                        brojac=1;
                        provjera = true;
                        red+=1;
                    }
                }
            }
            else{
                if(brojac == 1){
                    lista_susjedstva[j-brojPozicija].push_back({j,{' ',brojac2}});
                    lista_susjedstva[j].push_back({j-brojPozicija,{red,brojac2}});
                    if(brojac2==brojPozicija){
                        brojac=2;
                        red+=1;
                    }

                }
                else if(brojac==2){

                    if(provjeri(brojac2,red-1)){
                        lista_susjedstva[j-brojPozicija].push_back({j,{red-1,brojac2}});
                        lista_susjedstva[j].push_back({j-brojPozicija,{red,brojac2}});
                    }
                    if(brojac2==brojPozicija){
                        brojac=1;
                        provjera = false;
                    }
                }

            }
            brojac2++;
        }

    }


}
int Labirint::vratiIndeks(char slovo,int vrijednost){
    for(int i(0);i<lista_susjedstva.size();i++){
        for(auto el:lista_susjedstva[i]){
            if(el.second.first == slovo && el.second.second == vrijednost) return i;
        }
    }
    int broj = abs('A'-slovo)+1;
    if(broj%2==0){
        return (broj+broj-1)*(brojPozicija)+(vrijednost-1);
    }

    return -1;
}
int Labirint::udaljenosti(char r1,int pocetni,char r2,int krajnji) {
    int slovo1 = abs('A'-r1)+1;
    int slovo2 = abs('A'-r2)+1;
    if(pocetni > brojPozicija || pocetni < 0 || krajnji > brojPozicija || krajnji < 0)
        throw "Pogresan unos!";
    if(r1 > 'Z' || r1 < 'A' || r2 > 'Z' || r2 < 'A' || slovo1 > brojRedova || slovo2 > brojRedova)
        throw "Pogresan unos!";

    int n = lista_susjedstva.size();
    if(provjeri(pocetni,r1)) throw "Pocetni zid ne postoji!";
    if(provjeri(krajnji,r2)) throw "Krajnji zid ne postoji!";
    pocetni = vratiIndeks(r1,pocetni);
    krajnji = vratiIndeks(r2,krajnji);
    if(pocetni == -1 || krajnji == -1) throw "Put ne postoji!";
    vector<int> udaljenost(n, -1);
    vector<int> prethodnik(n, -1);
    udaljenost[pocetni] = 0;
    prethodnik[pocetni] = -2;
    queue<int> red;
    red.push(pocetni);
    while(!red.empty()) {
        int trenutni = red.front();
        red.pop();
        for(auto el:lista_susjedstva[trenutni]) {
            if(udaljenost[el.first] == -1) {
                udaljenost[el.first] = udaljenost[trenutni] + 1;
                prethodnik[el.first] = trenutni;
                  red.push(el.first);
            }
        }
        if(udaljenost[krajnji] != -1){
            break;
        }

    }
    if(udaljenost[krajnji] == -1){
        throw "Put ne postoji!";
    }
    //pronaci put
    int trenutni = krajnji;
    put.push_back(krajnji);
    do {
        trenutni = prethodnik[trenutni];
        put.push_back(trenutni);
    } while(trenutni != pocetni);

    reverse(put.begin(), put.end());
    put.pop_back();
    put.erase(put.begin());
    for(int i(0);i<put.size();i++) cout<<put[i]<<" ";
    cout<<endl;

    return udaljenost[krajnji]-1;
}
bool Labirint::provjeriIndeksZaPut(int i) {
    if (find(put.begin(), put.end(), i) != put.end()) {

        return true;
    } else {

        return false;
    }
}
void Labirint::iscrtajPut(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int n = lista_susjedstva.size();
    bool promjena = false;
    int brojac = 1;
    int brojac1 = 0;
    char red = 'B';

    int sirinaPolja = 3;

    cout << 'A' << ": ";
    for(int i(0); i < brojPozicija; i++) cout << setw(sirinaPolja) << left << i+1;
    cout << endl;

    for (int i = brojPozicija; i < n; i++) {
        brojac1++;
        if(brojac1 > brojPozicija){
            brojac1 = 1;
            brojac++;
            cout << endl;
        }
        if(brojac > 2){
            promjena = !promjena;
            brojac = 1;
        }
        if(promjena == true && brojac1 == 1){
            cout << red << ": ";
            red += 1;
        }
        if(promjena == false && brojac1 == 1){
            cout << "   ";
        }

        if(!promjena){
            if(provjeriIndeksZaPut(i)){
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                cout << setw(sirinaPolja) << left << 'X';
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            } else {
                cout << setw(sirinaPolja) << left << " ";
            }
        }
        if(promjena){
            if(provjeriIndeksZaPut(i)){
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                cout << setw(sirinaPolja) << left << 'X';
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            } else {

                if(provjeri(brojac1,red) && brojac == 1 || provjeri(brojac1,red-1) && brojac == 2)
                    cout << setw(sirinaPolja) << left << " ";
                else
                    cout << setw(sirinaPolja) << left << brojac1;
            }
        }
    }
    cout << endl;
}
