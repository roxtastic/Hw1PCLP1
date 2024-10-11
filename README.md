## TASK 1: ##
In functia flip_horizontal, am declarat un pointer nul pe nume temp pentru a putea face interschimbarea valorilor in cadrul inversarii orizontale a pixelilor din poza. 
Dupa, prin doua for-uri, am implementat interschimbarea. Functia returneaza matricea poza modificata conform cerintei. 
Astfel, nu exista nevoia de a elibera spatiul alocat matricei, deoarece nu a fost nevoie sa mutam rezultatul interschimbarii in alta matrice.

## TASK 2: ##
In functia rotate_left, am alocat spatiu unei alte matrice, si anume image2, pentru a stoca rezultatul cerut in enunt, in urma rotirii matricei cu 90 de grade la stanga.
In continuare, prin 2 for-uri, am interschimbat elementele conform unei asocieri de variabile identificate ca fiind cea necesara pentru a roti matricea, adica am echivalat rotirea cu o egalitate de indici.
In final, am returnat matricea modificata, image2.

## TASK 3: ##
In functia crop, folosesc o matrice image2 pentru a stoca rezultatul croparii. Daca suprafata cropata depaseste marginile imaginii, va fi umpluta cu valori "0", adica va fi un spatiu negru.
Pentru a realiza croparea, folosesc 2 for-uri si un if, prin care verific daca toti pixelii incadrati in suprafata ce se doreste a fi taiata apartin imaginii initiale. In acest caz, image2 preia pixel cu pixel ce apartine pozei si functia returneaza image2.

## TASK 4: ##
In functia extend, am alocat spatiu unei matrice extdimage, in care stochez imaginea extinsa. Mai intai, calculez noile dimensiuni ale imaginii, dupa aloc spatiul, dupa initializez pixelii noi si cantitatea lor de rosu, verde si albastru. Apoi, copiez prin interschimbare matricea initiala.


## TASK 5: ##
In functia paste, se lipeste o imagine pe imaginea initiala. valid_N si valid_M reprezinta dimensiunile valide ale imaginii sursa care pot fi copiate in imaginea destinatie, evitand astfel accesul in afara limitelor imaginii destinatie.
Un set de foruri parcurge pixelii imaginii sursa si ii copiaza in imaginea destinatie, incepand de la pozitia specificata (x, y). Aceasta se face pentru fiecare canal de culoare (R, G, B), unde k este 0 pentru rosu, 1 pentru verde si 2 pentru albastru.
Functia returneaza imaginea destinatie modificata.


## TASK 6: ##
Functia clamp limiteaza o valoare la un interval specificat intre 0 si magicnum255. Functia apply_filter aplica un filtru pe o imagine tridimensionala utilizand o matrice de filtru data (filter). Rezultatul este o noua imagine, iar fiecare pixel al imaginii rezultate este calculat prin convolutia pixelilor imaginii originale cu filtrul, iar apoi aplicand functia clamp pentru a asigura ca valorile raman in intervalul [0, magicnum255].
In functia apply_filter, am folosit:
Pentru a crea o noua imagine (result), am folosit malloc pentru a aloca spatiu pentru un tablou tridimensional de dimensiuni N x M x 3.
Apoi, am alocat spatiul pentru fiecare linie si coloana a imaginii.
Am aplicat un filtru pe fiecare pixel al imaginii originale. Pentru fiecare pixel, am iterat prin elementele filtrului si am calculat suma ponderata a canalelor de culoare (R, G, B) ale pixelilor invecinati.
Aceste sume ponderate sunt utilizate pentru a calcula noile valori ale canalelor de culoare pentru pixelul rezultat.
Pentru a asigura ca valorile rezultate raman intr-un interval specificat ([0, magicnum255]), am folosit functia clamp. Aceasta verifica daca valoarea este mai mica decat 0 si o fixeaza la 0, sau daca este mai mare decat magicnum255 si o fixeaza la magicnum255.
Functia clamp este apelata pentru a limita valorile sumelor ponderate la intervalul dorit.
Astfel, functia apply_filter combina operatii matematice si gestionare a memoriei pentru a aplica un filtru pe o imagine data.


## TASK 7: ##
Se utilizeaza malloc pentru alocarea dinamica de memorie pentru imagini si filtre.
Un tablou tridimensional images este creat pentru a stoca pixelii imaginilor. Alocarea de memorie pentru imagini se realizeaza folosind un pointer triplu catre un tablou bidimensional de pointeri catre un tablou unidimensional de pixeli.
Un tablou bidimensional filters este creat pentru a stoca matricele de filtru.
Programul ofera comenzi pentru citirea (l) si scrierea (s) de imagini BMP. Cand o imagine este citita, se aloca memorie pentru pixelii acesteia, iar cand este scrisa, memoria este eliberata corespunzator.
Operatii precum flip orizontal (ah), rotatie la stanga (ar), decupare (ac), extindere (ae), si lipire (ap) sunt implementate prin manipularea corespunzatoare a pixelilor in cadrul tablourilor tridimensionale.
Se permit utilizatorului sa defineasca si sa aplice filtre (cf si af). Fiecare filtru este reprezentat printr-o matrice bidimensionala de coeficienti. Memoria pentru fiecare filtru este alocata dinamic.
Pentru aplicarea filtrului, se utilizeaza o functie (apply_filter) care realizeaza o convolutie intre matricea filtrului si pixelii imaginii.
La finalul programului, se efectueaza o gestionare atenta a memoriei pentru a evita memory leaks. Pentru fiecare imagine si filtru, se parcurge si se elibereaza memoria alocata in mod dinamic pentru a preveni pierderile de resurse.
Programul ruleaza intr-o bucla infinita pana cand se primeste comanda de iesire (e). Acest design permite utilizatorului sa efectueze mai multe operatiuni intr-o sesiune.
Se folosesc constante predefinite pentru a face codul mai usor de inteles. De exemplu, constantele Magic_number15, Magic_number100, Magic_number250 si Magic_number50 sunt folosite pentru a specifica limite sau dimensiuni predefinite.
In esenta, programul combina manipularea imaginilor BMP cu gestionarea dinamica a memoriei si aplicarea de filtre matriceale pentru a oferi utilizatorului unelte extinse de procesare a imaginilor. Este important de mentionat ca, pe langa detaliile mentionate, functiile specifice si logica detaliata a fiecarei operatiuni contribuie la complexitatea si functionalitatea programului.



## TASK 8: ##
Nu am apucat sa il rezolv.