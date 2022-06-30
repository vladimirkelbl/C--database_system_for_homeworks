#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logic_for_database.h"

int main()
{
    t_database main_homeworks = init();     //nahodne nacte jenden ze souboru ve slozce a udela z nej dynamicky alokovanou databazi

    unsigned short int end = 0, skip = 0;
    char state[20] = "M", report[1024] = {0};

    //nasledujici oblast zapoznamkovat pro prvotni zobrazeni "nepekne" formatovane databaze
    char correcting_size_of_window[40] = {0};
    printf("\n\n%20cZadejte heslo, ktere je zasifrovane v dokumentaci projektu,%22caby se prokazalo ze jste dokumentaci cetl/a.", '\0', '\0');
    printf("\n\n%20cHeslo: ", '\0');
    gets(correcting_size_of_window);
    //zde ukonci poznamkovani

    while (1) {
        system("clear");
        show_database(main_homeworks);
        printf("\n\n\t%s\n", report);   //hlaseni o provedenych upravach databaze
        strcpy(report, "");     //aby se nezobrazovala stara hlaseni
        switch (state[0]) {
            //Menu
            case 'M':   printf("\n\n%20c\tMENU\n\n%9cVyberte: 1 - pridat polozku na konec databaze\n%18c2 - nacist polozky z CSV souboru na konec databaze\n%18c3 - smazat polozku podle ID\n%18c4 - setridit databazi podle vybraneho sloupce\n%18c5 - ulozit databazi do CSV souboru\n%18c0 - ukoncit program",'\0','\0', '\0', '\0', '\0', '\0', '\0');
                        skip = 0;
                        break;
            //pridat polozku
            case '1':   main_homeworks = add_item(main_homeworks);
                        strcpy(state, "M");
                        skip = 1;
                        strcpy(report, "Zvoleno: 1\n\tPolozka byla uspesne pridana na konec databaze.");
                        break;
            //nacist csv
            case '2':   main_homeworks = append_csv(main_homeworks);
                        strcpy(state, "M");
                        skip = 1;
                        strcpy(report, "Zvoleno: 2\n\tCSV soubor byl uspesne nacten na konec databaze.");
                        break;
            //smazat polozku
            case '3':   main_homeworks = delete_item(main_homeworks);
                        strcpy(state, "M");
                        skip = 1;
                        strcpy(report, "Zvoleno: 3\n\tPolozka byla uspesne smazana.");
                        break;
            //trideni
            case '4':   //main_homeworks = sort_homeworks(&(main_homeworks.first), &(main_homeworks.last));
                        sort_homeworks(&(main_homeworks.first), &(main_homeworks.last));
                        strcpy(state, "M");
                        skip = 1;
                        strcpy(report, "Zvoleno: 4\n\tDatabaze byla uspesne setridena.");
                        break;
            //ulozeni
            case '5':   save_to_csv(main_homeworks);
                        strcpy(state, "M");
                        skip = 1;
                        strcpy(report, "Zvoleno: 5\n\tDatabaze byla uspesne ulozena do csv souboru.");
                        break;
            //konec programu
            case '0':   end = 1;
                        break;
            //neplatny vstup
            default:    strcpy(state, "M");
                        skip = 1;
                        strcpy(report, "Zvoleno: chyba\n\tByla zadana neplatna volba. Zkuste prosim znovu.");
                        break;
        }
        if (end) break;
        if (skip) {
            continue;
        } else {
            printf("\n\n%6cVase volba: ", '\0');
            gets(state);
        }
    }
    printf("\n\n\n\n\n\n%20cNa schledanou\n", '\0');
    clear_and_end(main_homeworks);
    return 0;
}
