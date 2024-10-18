/*
Projektni zadatak iz predmeta Napredno C programiranje u realnom vremenu
Student: Jovan Crncevic, RA129/2021
Profesor: doc. dr Miodrag Djukic

Opis zadatka:
Napisati program koji pravi recnik na osnovu zadatog teksta (leksikografski uredjen skup reci koje se javljaju u tom tekstu).
Napraviti od toga modul i realizovati ga kao dinamicku biblioteku sa dinamickim povezivanjem tokom izvrsavanja.
Tu biblioteku ukljuciti u glavni program koji ce obavljati komunikaciju sa okruzenjem (unos/ispis i slicno).

Opis resenja:

Napomene:
Pretpostavimo da radimo u vremenski i hardverski ogranicenom okruzenju tako da koristimo staticku alokaciju memorije zbog brzine i bezbednosti.
Ogranicavamo duzinu teksta, kao i duzinu i broj reci koriscenjem pretprocesorskih direktiva. Vrednosti se uvek mogu menjati unutar .h fajla.
Program ne gleda reci od jednog slova, brojeve, niti ostale znake interpunkcije. Jedino sto dolazi u obzir su reci od 2 do MAX_SIZE slova.
Napraviti spisak gresaka vracanja funkcija.
Program je provucen kroz style50 da potvrdim pravilan koding standard.

main.c:
Ne vrsi se provera broja unetih karaktera, korisniku je eksplicitno navedeno, ukoliko se pravilo ne ispostuje funkcija fgets ce
odseci visak karakera i proslediti odsecen tekst. Izabrao sam ovo kako bismo ustedeli resurse za proveru necega sto nece crashovati program.

dictionary.c:
Bolji pristup bi bio provera duplikat reci u samom tekstu pre nego sto se prodje kroz separate, ali je vremenski zahtevna i odlucio sam se za
ovaj pristup po cenu neiskoricene memorije.

Izbegavanje koriscenja string.h
Pretpostavke kojih se treba drzati tokom unosa teksta

Prenosivost, preporuka pisati signed char

Mane zadatka
*/

#include <stdio.h>
#include "dictionary.h"

int main()
{
    char text[TEXT_MAX_SIZE];
    char dictionary[WORD_MAX_COUNT][WORD_MAX_SIZE];

    printf("Enter text not longer than %d characters, including blank spaces: ", TEXT_MAX_SIZE - 1);
    fgets(text, TEXT_MAX_SIZE, stdin);

    makeDictionary(text, dictionary);
    printDictionary(dictionary);

    return 0;
}