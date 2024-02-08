*Dokumentacija Projekta "Labirint"*


#1. Uvod
Projekat "Labirint" predstavlja implementaciju algoritma za pronalaženje puta kroz
labirint. Osnovna namjena ovog projekta je demonstracija upotrebe grafova i algoritama
pretrage, posebno Breadth-First Search (BFS), u rješavanju problema pronalaženja puta
kroz labirint.
#2. Opis Klase: Labirint
Klasa Labirint predstavlja osnovu projekta. Ova klasa upravlja strukturalnim elementima
labirinta, uključujući čvorove, prolaze, i zidove, te pruža funkcionalnosti za pronalaženje
puta.
#Atributi Klase:
• int brojRedova: Broj redova u labirintu.
• int brojPozicija: Broj pozicija (čvorova) u svakom redu.
• vector<list<pair<int,pair<char,int>>>> lista_susjedstva: Lista susjedstva koja
predstavlja strukturu grafa labirinta.
• map<char, set<int>> prolazi: Mapa koja sadrži informacije o prolazima između
redova u labirintu.
• vector<int> put: Vektor koji sadrži put kroz labirint.
#3. Metode Klase
Labirint()
• Opis: Konstruktor klase. Inicijalizira osnovne parametre labirinta.
• Parametri: Nema.
• Povratna vrijednost: Nema.
ucitajIzFajla(const string& fileName)
• Opis: Učitava podatke labirinta iz specificiranog fajla.
• Parametri: fileName - putanja do fajla sa podacima labirinta.
• Povratna vrijednost: Nema.
udaljenosti(char pocetniRed, int pocetnaPozicija, char krajnjiRed, int krajnjaPozicija)
• Opis: Vraća udaljenost i put između dva čvora u labirintu.
• Parametri: pocetniRed, pocetnaPozicija - početni čvor; krajnjiRed, krajnjaPozicija -
krajnji čvor.
• Povratna vrijednost: Udaljenost između čvorova.
iscrtajPut()
• Opis: Iscrtava pronađeni put kroz labirint.
• Parametri: Nema.
• Povratna vrijednost: Nema.
#4. Implementacijski Detalji
Labirint je implementiran kao usmjereni, netežinski graf. Svako polje u labirintu
predstavljeno je kao čvor u grafu. Lista susjedstva koristi se za predstavljanje veza
između čvorova. Prolazi između redova su specificirani i implementirani vertikalno, dok
horizontalni prolazi između zidova nisu omogućeni.
BFS algoritam se koristi za pronalaženje jednog od najkraćih puteva kroz labirint. Za
svaki čvor, pamtimo koji čvor ga je dodao (roditelj), što omogućava rekonstrukciju puta
nakon završetka pretrage.
#5. Primjer upotrebe
#6. Zaključak
Projekat "Labirint" uspješno demonstrira primjenu algoritama pretrage u rješavanju
problema pronalaženja puta. Dodatna unapređenja mogu uključivati implementaciju
različitih vrsta algoritama za pretragu, kao i poboljšanja u vizualizaciji labirinta.
#7. Dodaci
• Preporučeni kompajler: GCC, verzija 9.3.0.
• Dodatna uputstva: Ako koristite Windows, potrebno je da imate instaliran
windows.h za ispravno funkcionisanje programa.
#8. Reference
• Algoritmi za pretragu grafova.
• Dokumentacija standardne biblioteke C++.
Ova dokumentacija pruža osnovne informacije o korištenju i funkcionalnostima projekta
"Labirint". Dalje proširenje dokumentacije može uključivati detaljnije opise
implementacije i napredne primjere korištenja.
