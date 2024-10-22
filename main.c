/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*   Projektni zadatak iz predmeta Napredno C programiranje u realnom vremenu    *
*   Student: Jovan Crncevic, RA129/2021                                         *
*   Profesor: doc. dr Miodrag Djukic                                            *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

> Opis zadatka:
    - Napisati program koji pravi recnik na osnovu zadatog teksta (leksikografski
      uredjen skup reci koje se javljaju u tom tekstu). Napraviti od toga modul i
      realizovati ga kao dinamicku biblioteku sa dinamickim povezivanjem tokom
      izvrsavanja. Tu biblioteku ukljuciti u glavni program koji ce obavljati
      komunikaciju sa okruzenjem (unos/ispis i slicno).

> Opis resenja:
    - Resenje zadatka je implementirano u okviru dictionary.c fajla kojem odgovara
      dictionary.h header. Funkcije koje korisnik moze da koristi su
      makeDictionary() i printDictionary(). Funkcije koje se pozivaju tokom pravljenja
      recnika su odvajanje reci, brisanje duplikata, sortiranje preostalih reci i,
      ukoliko je GENERATE_OUTPUT_FILE flag postavljen na 1, generisanje dictionary.txt
      fajla u kojem su smestene reci. Funkcija ispisivanja se moze, a i ne mora
      pozivati odvojeno, u zavisnosti od toga da li korisniku treba ispis ili samo
      zeli da barata recnikom na neki drugi nacin.

> Napomene:
    - Pretpostavljamo da radimo u vremenski i hardverski ogranicenom okruzenju.
    - Kroz ceo zadatak cu teziti tome da program radi sto brze, u nekim slucajevima
      i po cenu koriscenja dodatne memorije. Kada su kratki tekstovi u pitanju razlika
      u vremenu nije toliko primetna, ali kada na ulaz programa stigne dugacak tekst,
      stvari se menjaju (detaljnije o tome u rezultatima testiranja).
    - Mnogo paznje sam posvetio algoritmu za sortiranje i izabrao sam quick sort jer
      je dobra kombinacija koriscenja memorije i vremena. Vremenska slozenost ce mu
      uglavnom biti O(n*logn), a najgori slucaj O(n^2) je u situaciji kada mu na ulaz
      stigne vec sortiran niz, sto ce se u praksi sa tekstovima veoma retko desavati.
    - Takodje, odlucio sam se za staticku alokaciju memorije. Na osnovu razlicitih
      izvora zakljucio sam da je brza i efikasnija, ali i bezbednija, sto je posebno
      bitno za embedded sisteme i rad u realnom vremenu, jer npr. svako nepredvidjeno
      curenje memorije moze izazvati problem.
    - Sto se hardverskog ogranicenja tice, to sam resio koriscenjem pretprocesorskih
      direktiva (detaljnije o tome u delu za prenosivost).

> Dodatna usteda resursa:
    - fgets() funkcija ce odseci deo teksta koji prelazi velicinu od TEXT_MAX_SIZE,
      tako da ne moramo da gubimo vreme na proveru duzine.
    - Tokom programa smanjujem maksimalnu vrednost do koje brojac moze da ide. Iako
      je WORD_MAX_COUNT postavljen na odredjenu cifru, nakon odvajanja reci broj
      koji se prosledjuje brisanju duplikata je broj reci koje se zapravo nalaze u
      tekstu, a onda se sortiranju reci prosledjuje broj preostalih reci nakon
      brisanja duplikata.
    - Redosled linija (npr. u main- u ne vrsim alokaciju memorije i pozive funkcija
      dok ne prodju sve provere validnosti poziva i ulaznog teksta).

> Prenosivost:
    - Koriscene su samo standardne C biblioteke (po C17 standardu).
    - Lako moze da se ogranicava memorija menjanjem pretprocesorskih direktiva,
      u zavisnosti od nasih potreba i ogranicenja.
    - Lako moze da se menja tip promenljive brojaca i format specifikator za ispis
      menjanjem pretprocesorskih direktiva.
    - Razlicita okruzenja na char gledaju drugacije, neki kao signed, neki kao unsigned.
      U kontekstu ovog zadatka i prenosivosti nije bitno, jer baratamo karakterima iz
      ASCII tabele, a oni u oba slucaja upadaju u raspolozivi opseg char tipa.

> Pretprocesorske direktive:
    - TEXT_MAX_SIZE - maksimalna duzina teksta koja moze doci na ulaz.
    - WORD_MAX_SIZE - maksimalna duzina reci u tekstu.
    - WORD_MAX_COUNT - maksimalan broj reci u tekstu.
    - COUNTER_TYPE - tip brojaca kroz program (za najbolju efikasnost potrebno je da
                     podrzava vrednosti najveceg broja izmedju 3 prethodne
                     pretprocesorske direktive i ne vise od toga, npr. ako je najveca
                     vrednost TEXT_MAX_SIZE 30000, nema potrebe za int32, dovoljan je
                     int16; int_fast16_t zbog brzine).
    - COUNTER_SPECIFIER - trebalo bi da se poklapa sa COUNTER_TYPE i da bude namenjen
                          printf() funkciji (npr. za int_fast16_t se koristi PRIdFAST16).
    - GENERATE_OUTPUT_FILE - postavlja se na 1 ako zelimo da generisemo dictionary.txt
                             fajl, odnosno na 0 ako ne zelimo.

> Testiranje:
    - Testiranje sam poceo tako sto sam na ulaz prosledjivao razne tekstove razlicitih
      duzina, kombinacija karaktera, sortiranja, duplikata. Na osnovu izlaza, najvise
      izmena sam pravio u separateWords() funkciji, dok nisam dobio zeljene rezultate.
    - U prvoj verziji, program je imao samo unos teksta iz terminala, ali sam primetio
      da fgets() ogranicava ulaz na maksimalno 4096 karaktera, bez obzira na to da li je
      TEXT_MAX_SIZE postavljen na vise od toga, tako da sam zbog duzih tekstova uveo
      i citanje iz fajla.
    - Dobar deo vremena sam potrosio na izbor algoritma za sortiranje reci, pogotovo
      izbor izmedju merge i quick sort. Merge je dobar jer mu je vremenska slozenost
      uvek fiksna i iznosti O(n*logn), ali koristi vise memorije od quick sort- a,
      a kako sam vec naveo, najgori slucaj quick sort- a ce se veoma retko desavati
      tako da sam izabrao njega i pored vremena ustedeo i na memoriji.
    - Program je na ulaze koji pocinju praznim redom bacao segmentation fault, pa sam
      napravio zastitu i za to.
    - Program je provucen kroz style50 da se potvrdi vecina stavki iz koding standarda.
    - Program je testiran na MISRA pravila.

> Rezultati testiranja:
    - Da bih potvrdio teoriju o sortiranju, koristio sam funkciju clock() kako bih
      dobio vreme izvrsavanja programa kada se koriste 3 razlicita tipa sortiranja:

      * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
      * FAJL          * QUICK SORT    * MERGE SORT    * BUBBLE SORT   *
      * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
      * test_1.txt    * 0.126572s     * 0.126596s     * 0.649766s     *
      * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
      * test_2.txt    * 0.021502s     * 0.021579s     * 0.024576s     *
      * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
      * test_3.txt    * 2.289610s     * 2.299813s     * 4.380709s     *
      * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

    - Iz ovoga jasno vidimo da su i merge i quick sort daleko efikasniji od bubble
      sort- a, pogotovo za duze tekstove. Vremena quick i merge sort- a jedva da se
      razlikuju, a posto quick koristi manje memorije, ostaje prvi izbor.

> Neispostovana MISRA pravila:
    - (MISRA-C:2004 5.6/A) No identifier in one name space should have the same spelling
      as an identifier in another name space, with the exception of structure member and
      union member names.
    - (MISRA-C:2004 5.7/A) No identifier name should be reused.
    - (MISRA-C:2004 6.1/R) The plain char type shall be used only for the storage and use
      of character values.
    - (MISRA-C:2004 10.1/R) The value of an expression of integer type shall not be
      implicitly converted to a different underlying type if it is not a conversion to a
      wider integer type of the same signedness.
    - (MISRA-C:2004 12.2/R) The value of an expression shall be the same under any order
      of evaluation that the standard permits.
    - (MISRA-C:2004 13.5/R) The three expressions of a for statement shall be concerned
      only with loop control.
    - (MISRA-C:2004 14.7/R) A function shall have a single point of exit at the end of
      the function.
    - (MISRA-C:2004 17.4/R) Array indexing shall be the only allowed form of
      pointer arithmetic.
    - (MISRA-C:2004 20.9/R) The input/output library <stdio.h> shall not be used in
      production code.

> Mane resenja:
    - Ako ogranicimo tekst na 10000 karaktera medju kojima je 1000 reci i ogranicimo
      broj reci u recniku na 1000, nikad necemo iskoristiti pun potencijal zauzete
      memorije jer je staticki alocirana, a na brisanje duplikata mozemo izgubiti
      znacajan procenat reci koje ce se upisati u recnik (resenje bi bilo da se
      duplikati brisu iz teksta pre nego sto se reci odvoje).
    - Neispostovana MISRA pravila.

> Proces kompajliranja i pozivanja:
    - U zadatku je potrebno realizovati modul kao dinamicku biblioteku sa dinamickim
      povezivanjem tokom izvrsavanja.
    - Koraci tokom kompajliranja su (dictionary folder):
        1) gcc -c -fpic dictionary.c (objektna datoteka).
        2) gcc -shared -o libdictionary.so dictionary.o (dinamicka biblioteka).
        3) gcc main.c -I dictionary/ -L dictionary/ -l dictionary.
    - Koraci tokom pokretanja programa (glavni folder):
        1) export LD_LIBRARY_PATH=:dictionary/ (promenljiva okruzenja).
        2.1) ./a.out 1 (za unos teksta kroz terminal).
        2.2) ./a.out 2 naziv_ulaznog_fajla.txt (za citanje teksta iz fajla).

> Velicina izvrsne datoteke:
    - Koriscenjem ls -sh a.out dobio sam vrednost od 20 KB.
*/

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

int main(int argc, char* argv[])
{
    if (!(((argc == 2) && (atoi(argv[1]) == 1)) || ((argc == 3) && (atoi(argv[1]) == 2))))
    {
        printf("Wrong format. Call the program using:\n%s 1, if you want to type the text, or\n"
               "%s 2 INPUT_FILE_NAME, if you want to use the text from existing file\n", argv[0], argv[0]);
        return 1;
    }

    char text[TEXT_MAX_SIZE] = {'\0'};

    if (atoi(argv[1]) == 1)
    {
        printf("Enter text: ");
        fgets(text, TEXT_MAX_SIZE, stdin);
    }
    else
    {
        FILE *file = fopen(argv[2], "r");

        if (file == NULL)
        {
            perror("Error opening input file");
            return 2;
        }

        if (fgets(text, TEXT_MAX_SIZE, file) == NULL)
        {
            perror("Error reading input file");
            return 3;
        }

        fclose(file);
    }

    if (text[0] == '\n')
    {
      printf("Do not start the text with a blank line\n");
      return 4;
    }

    char dictionary[WORD_MAX_COUNT][WORD_MAX_SIZE] = {'\0'};

    void* handle;
    void (*makeDict)(const char[], char[][WORD_MAX_SIZE]);
    void (*printDict)(const char[][WORD_MAX_SIZE]);
    char* error;

    handle = dlopen("libdictionary.so", RTLD_LAZY);
    if (handle == NULL)
    {
      fputs(dlerror(), stderr);
      exit(1);
    }

    makeDict = dlsym(handle, "makeDictionary");
    if ((error = dlerror()) != NULL)
    {
      fputs(error, stderr);
      exit(1);
    }

    printDict = dlsym(handle, "printDictionary");
    if ((error = dlerror()) != NULL)
    {
      fputs(error, stderr);
      exit(1);
    }

    (*makeDict)(text, dictionary);
    (*printDict)(dictionary);

    dlclose(handle);

    return 0;
}
