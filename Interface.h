//
// Created by krispy1396 on 12.11.2017.
//

#ifndef ZMPO_LISTA3_INTERFACE_H
#define ZMPO_LISTA3_INTERFACE_H

#include "Tree.h"
#include <iostream>

using namespace std;

const char *ENTER_INSTRUCTION = "enter";
const char *VARS_INSTRUCTION = "vars";
const char *PRINT_INSTRUCTION = "print";
const char *COMP_INSTRUCTION = "comp";
const char *JOIN_INSTRUCTION = "join";
const char *END_INSTRUCTION = "end";

const char *OPERATION_PROMPT = "\nPodaj polecenie: ";

const char *HELLO_MESSAGE = "***** Witaj w programie do obslugi formul matematycznych! *****\n"
        "Dostepne polecenia:\n"
        "1) enter <formula>\n"
        "       Wczytanie drzewa na podstawie podanego wyrazenia.\n"
        "       Jezeli wyrazenie posiada bledy nastepuje proba jego naprawienia\n"
        "2) vars\n"
        "       Wypisuje (bez powtorzen) wszystkie zmienne przechowywane w drzewie\n"
        "3) print\n"
        "       Wypisuje aktualnie wprowadzone drzewo w postaci prefiksowej\n"
        "4) comp <var0> <var1> ... <varN>\n"
        "       Wyliczenie wartosci formuly dla argumentow okreslonych w vars\n"
        "       przyjmujacych wartosci okreslone w <var0> <var1> ... <varN>\n"
        "5) join <formula>\n"
        "       Tworzy drzewo stowrzone z polaczenia biezacego drzewa\n"
        "       z drzewem stworzonym z podanej formuly\n"
        "6) end\n"
        "       Konczy program\n"
        "***********************************************************";

class Interface {
public:
    static void showInterface();
};


#endif //ZMPO_LISTA3_INTERFACE_H
