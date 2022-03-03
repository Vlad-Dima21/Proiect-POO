# Proiect-POO
Programul are ca scop gestionarea unui centru de organizari de petreceri onomastice pentru copii. El permite utilizatorului să verifice 
locațile disponibile spre inchiriere, intervalele orare disponibile cât și costul inchirierii.
Administratorul poate adăuga/sterge locatii, schimba tarifele cât și atributele unei locatii și gestiona produsele și animatorii.

Proiectul a fost realizat în mai multe etape.

## Cerințe obligatorii:

* Implementare în C++
* Programul să aibă un meniu interactiv
* Programul să nu conțină erori de compilare
* Pentru orice porțiune de cod inclusă din alte surse trebuie citată sursa în
  comentarii.
* Orice variabilă/concept folosit în proiect trebuie justificat, nu se acceptă
folosirea variabilelor/conceptelor doar pentru a se puncta.
* Code Design

## Etapa 1:

* Aplicația trebuie să conțină minim 4 clase.
* Alegerea claselor trebuie să fie cat mai logică, astfel fiecare clasă sa aibă
  legătură una cu cealaltă.
* În aceste clase trebuie să existe variabile de următoarele tipuri (toate):
  - Int/long
  - Bool
  - Char
  - Char*
  - Floate
  - Int*
  - Float*
  - Double
  - Const
  - Static
  - String
  - String*
* Pentru 2 din clase să se construiască Setters și Getters.
* Pentru fiecare clasă:
  - Cel puțin 2 constructori cu parametrii (unul din parametrii trebuie să
    fie Const și/sau Static)
  - Constructorul fară parametrii
  - Contructorul de copiere
  - Destructor
  - Forma supraîncărcată a operatorului =
  - Supraîncărcarea operatorului << și >>
* Să se supraîncarce pentru fiecare clasă:
  - Operatorul de indexare []
  - Operatorul ++ sau -- (cele două forme)
  - Minim 2 operatori matematici (+,-,* sau /)
  - Operatorul cast explicit sau implicit
  - Un operator condițional (<, ><=, >=)
  - Operatorul pentru egalitate (==)
* Fiecare clasă să conțină o funcționalitate.

## Etapa 2:

* Cerințele de la Etapa 1
* Extinderea a minim 2 din clasele definite în etapa anterioară prin adăugarea
  de atribute noi și metode noi; extinderea se face doar prin derivare (Relația IS
  A) si NU prin modificarea claselor
* Să se implementeze minim o clasă abstractă (cu sau fară atribute) ce trebuie
  să conțină minim o metodă virtuală pură.
* Să se implementeze minim o interfață care va conține minim o metodă virtuală
* Să se implementeze o clasă care exemplifică conceptul de HAS A
* Să se exemplifice conceptul de virtualizare
* Interfețele/Clasele Abstracte să respecte o formă de ierarhie a claselor

## Etapa 3:

* Să se implementeze din librăria STL cel puțin un vector, un set, o listă și un
  map pentru a gestiona datele aplicației.
* Scrierea și citirea din fișier
* Aplicația va conține un meniu (în consolă) prin care utilizatorul poate alege
  diverse opțiuni (import/export date, citire obiect nou de la tastatură, diverse
  functionalități ale aplicației)
