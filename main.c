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
      dictionary.h header. Funkcije koje bi korisnik trebalo da koristi su
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
      stvari se menjaju. Najvise paznje sam obratio na algoritam za sortiranje i
      izabrao sam merge sort jer mu je vremenska kompleksnost u svim slucajevima ista
      (nlogn).
    - Takodje, odlucio sam se za staticku alokaciju memorije. Na osnovu razlicitih
      izvora zakljucio sam da je brza i efikasnija, ali i bezbednija, sto je posebno
      bitno za embedded sisteme i rad u realnom vremenu, jer npr. svako nepredvidjeno
      curenje memorije moze izazvati problem.
    - Sto se hardverskog ogranicenja tice, to sam resio koriscenjem pretprocesorskih
      direktiva. Detaljnije o tome u delu za prenosivost.
    - main.c:
    - dictionary.c:

main.c:
Ne vrsi se provera broja unetih karaktera, korisniku je eksplicitno navedeno, ukoliko se pravilo ne ispostuje funkcija fgets ce
odseci visak karakera i proslediti odsecen tekst. Izabrao sam ovo kako bismo ustedeli resurse za proveru necega sto nece crashovati program.

dictionary.c:
Bolji pristup bi bio provera duplikat reci u samom tekstu pre nego sto se prodje kroz separate, ali je vremenski zahtevna i odlucio sam se za
ovaj pristup po cenu neiskoricene memorije.

> Prenosivost:
    - Koriscene su samo standardne C biblioteke (po C17 standardu).
    - Lako moze da se ogranicava memorija menjanjem pretprocesorskih direktiva,
      u zavisnosti od nasih potreba i ogranicenja.
    - Lako moze da se menja tip promenljive i format specifikator za ispis menjanjem
      pretprocesorskih direktiva, jer npr. ako se tekst ogranici na 200 karaktera,
      nema potrebe za int16.
    - Razlicita okruzenja na char gledaju drugacije, neki kao signed, neki kao unsigned.
      U kontekstu ovog zadatka i prenosivosti nije bitno, jer baratamo karakterima iz
      ASCII tabele, a oni u oba slucaja upadaju u raspolozivi opseg char tipa.

> Pretpostavke kojih se treba drzati tokom unosa teksta:
Tekst nece imati bespotrebna prazna mesta na pocetku i na kraju. Ne postoji funkcija koja

> Testiranje:
    - Program je provucen kroz style50 da se potvrdi pravilan koding standard.
    - Program je testiran na MISRA pravila.

> MISRA pravila 

> Mane resenja:
*/

#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"

int main(int argc, char* argv[])
{
    if (!((argc == 2 && atoi(argv[1]) == 1) || (argc == 3 && atoi(argv[1]) == 2)))
    {
        printf("Wrong format. Call the program using:\n%s 1, if you want to type the text, or\n"
               "%s 2 INPUT_FILE_NAME, if you want to use text from existing file\n", argv[0], argv[0]);
        return 1;
    }

    char text[TEXT_MAX_SIZE] = {'\0'};
    char dictionary[WORD_MAX_COUNT][WORD_MAX_SIZE] = {'\0'};

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

    makeDictionary(text, dictionary);
    printDictionary(dictionary);

    return 0;
}