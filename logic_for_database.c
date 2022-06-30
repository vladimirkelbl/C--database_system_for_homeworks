#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct homework {
    unsigned short int ID;                  //1
    char name[40];                          //2
    char theme[40];                         //3
    unsigned short int bonus_work;          //4
    unsigned short int main_part_difficulty;//5
    unsigned short int bonus_difficulty;    //6
    struct homework* next_homework;
} t_homework;

typedef struct database {
    t_homework* first;
    t_homework* last;
} t_database;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
t_database read_from_csv(char* str) {
    t_database new_homeworks;
    new_homeworks.first = NULL;
    new_homeworks.last = NULL;

    char buffer[60] = {0};
    FILE* input_file = fopen(str, "r");
    int column = 0;

    while (fgets(buffer, 60, input_file)) {
        char* value = strtok(buffer, ";");
        column = 0;
        t_homework* homework = (t_homework*)malloc(sizeof(t_homework));
        while (value) {                 //zde by to bylo lepsi pres switch, doslo mi to az kdyz jsem to mel cele napsane pres else if statementy
            // Column 1         //ID
            if (column == 0) {
                homework->ID = atoi(value);
            }
            // Column 2         //nazev ulohy
            else if (column == 1) {
                strcpy(homework->name, value);
            }
            // Column 3         //stezejni tema
            else if (column == 2) {
                strcpy(homework->theme, value);
            }
            // Column 4         //bonusovy priklad
            else if (column == 3) {
                homework->bonus_work = atoi(value);
            }
            // Column 5         //obtiznost ulohy
            else if (column == 4) {
                homework->main_part_difficulty = atoi(value);
            }
            // Column 6         //obtiznost bonusove ulohy
            else {
                homework->bonus_difficulty = atoi(value);
            }
            value = strtok(NULL, ";");
            column++;
        }

        if (new_homeworks.first == NULL) {
            new_homeworks.first = homework;
            new_homeworks.last = homework;
        } else {
            new_homeworks.last->next_homework = homework;
            new_homeworks.last = homework;
        }
    }
    fclose(input_file);
    return new_homeworks;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
t_database init() {
    srand(time(NULL));
    int temp = rand()%3;
    char str[40] = {0};

    switch (temp) {
        case 0:
            strcpy(str, "first_file.csv");
            break;
        case 1:
            strcpy(str, "second_file.csv");
            break;
        case 2:
            strcpy(str, "third_file.csv");
            break;
    }

    t_database homeworks = read_from_csv(str);
    return homeworks;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void show_database(t_database homeworks) {
    printf(" ID %14sNazev ulohy %12sStezejni tema %5sBonusovy priklad %5sObtiznost ulohy %5sObtiznost bonusoveho prikladu\n", " ", " ", " ", " ", " ");
    t_homework* tmp = homeworks.first;
    char str[4] = {0};

    do {
        if (tmp->bonus_work) strcpy(str, "ano");
        else strcpy(str, "ne");
        for (int i = 0; i < 133; i++)
            printf("-");
        printf("\n %2d %25s %25s %21s %15d / 10 %29d / 10\n", tmp->ID, tmp->name, tmp->theme, str, tmp->main_part_difficulty, tmp->bonus_difficulty);
        tmp = tmp->next_homework;
    } while (tmp != homeworks.last);

    if (tmp->bonus_work) strcpy(str, "ano");
    else strcpy(str, "ne");
    for (int i = 0; i < 133; i++)
        printf("-");
    printf("\n %2d %25s %25s %21s %15d / 10 %29d / 10\n", tmp->ID, tmp->name, tmp->theme, str, tmp->main_part_difficulty, tmp->bonus_difficulty);
    for (int i = 0; i < 133; i++)
        printf("-");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
t_database add_item(t_database homeworks) {
    char buffer[60] = {0};
    t_homework* homework = (t_homework*)malloc(sizeof(t_homework));

    printf("\n\n%20cPostupne zadejte jednotlive hodnoty nove polozky.", '\0');

    printf("\n\n\n%20cID: ", '\0');
    gets(buffer);
    homework->ID = atoi(buffer);

    printf("\n%20cNazev ulohy: ", '\0');
    gets(buffer);
    strcpy(homework->name, buffer);

    printf("\n%20cStezenjni tema: ", '\0');
    gets(buffer);
    strcpy(homework->theme, buffer);

    printf("\n%20cBonusovy priklad (1 = ano, 0 = ne): ", '\0');
    gets(buffer);
    homework->bonus_work = atoi(buffer);

    printf("\n%20cObtiznost ulohy (1 až 10, 10 je nejnarocnejsi): ", '\0');
    gets(buffer);
    homework->main_part_difficulty = atoi(buffer);

    printf("\n%20cObtiznost bonusoveho prikladu (1 až 10, 10 = nejnarocnejsi, 0 = bonusova uloha neni): ", '\0');
    gets(buffer);
    homework->bonus_difficulty = atoi(buffer);

    homeworks.last->next_homework = homework;
    homeworks.last = homework;

    return homeworks;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
t_database append_csv(t_database homeworks) {
    char buffer[20] = {0}, str[40] = {0};
    //unsigned short int file = 1;
    t_database homeworks_to_append;
    printf("\n\n%20cKtery CSV soubor chcete vybrat?\n\n%9cVyberte: 1 - first_file\n%18c2 - second_file\n%18c3 - third_file", '\0', '\0', '\0', '\0');
    printf("\n\n%6cVase volba: ", '\0');
    gets(buffer);

    switch (buffer[0]) {
        case '1':   strcpy(str, "first_file.csv");
                    break;

        case '2':   strcpy(str, "second_file.csv");
                    break;

        case '3':   strcpy(str, "third_file.csv");
                    break;

        default:    printf("\n\n\n%18cNebyl zadan platny soubor.\n%18c", '\0', '\0');
                    getchar();
                    return homeworks;
    }

    homeworks_to_append = read_from_csv(str);

    homeworks.last->next_homework = homeworks_to_append.first;
    homeworks.last = homeworks_to_append.last;
    return homeworks;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
t_database delete_item(t_database homeworks) {
    //kontorla jestli ma databaze více jak 2 polozky
    if (homeworks.first->next_homework == homeworks.last) {
        printf("\n\n%20cDatabaze ma jen 2 polozky. Nemuze mit mene.\n%20c", '\0', '\0');
        getchar();
        return homeworks;
    }

    char buffer[20] = {0};
    t_homework* homework_to_delete = homeworks.first, *previous_homework;

    printf("\n\n%20cKterou polozku chcete smazat?", '\0');
    printf("\n\n%20cID: ", '\0');
    gets(buffer);
    int tmp_ID = atoi(buffer), flag = 0;

    if (homeworks.first->ID == tmp_ID) {
        homeworks.first = homeworks.first->next_homework;
        free(homework_to_delete);
        return homeworks;
    }

    while (homework_to_delete != homeworks.last) {
        if (homework_to_delete->ID == tmp_ID) {
            flag = 1;
            break;
        }
        previous_homework = homework_to_delete;
        homework_to_delete = homework_to_delete->next_homework;
    }

    if (flag) {
        previous_homework->next_homework = homework_to_delete->next_homework;
        free(homework_to_delete);
    } else if (homeworks.last->ID == tmp_ID) {
        homeworks.last = previous_homework;
        free(homework_to_delete);
    } else {
        printf("\n\n%20cNebylo zadano platne ID.\n%20c", '\0', '\0');
        getchar();
    }
    return homeworks;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void change_two_pointers(t_homework **one, t_homework **two) {
    t_homework *tmp = *one;
    *one = *two;
    *two = tmp;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//t_database sort_homeworks(t_homework **first, t_homework **last) {
void sort_homeworks(t_homework **first, t_homework **last) {
    unsigned short int n, i, flag, length = 1;
    //t_homework **tmp = first;
    t_homework **tmp1 = first;
    t_homework **tmp2;

    //t_homework **ptmp = &tmp;

    // spocte delku sezanamu
    while (*tmp1 != *last) {     //takhle to chci protoze v dalsim radku prirazuji ukazatel na t_homework (protoze hodnotu bez hvezdicky v tele cyklu nemenim)
        *tmp1 = (*tmp1)->next_homework;
        length++;
    }

    printf("\n\nDelka:  %d\n\n", length);

    char buffer[20] = {0}, up_down[20] = {0};
    //t_homework* one;
    //t_homework* two;
    //t_homework *help;

    printf("\n\n%20cPodle ktere polozky chcete databazi tridit?", '\0');
    printf("\n\n%9cVyberte:   1 - ID", '\0');
    printf("\n%20c2 - Nazev ulohy", '\0');
    printf("\n%20c3 - Stezejni tema", '\0');
    printf("\n%20c4 - Bonusovy priklad", '\0');
    printf("\n%20c5 - Obtiznost ulohy", '\0');
    printf("\n%20c6 - Obtiznost bonusoveho prikladu", '\0');
    printf("\n\n%6cVaee volba:   ", '\0');
    gets(buffer);
    printf("\n\n\n%20cJakym smerem chcete databazi seradit?", '\0');
    printf("\n\n%9cVyberte:   0 - odshora sestupne", '\0');
    printf("\n%20c1 - odshora vzestupne", '\0');
    printf("\n\n%6cVase volba:   ", '\0');
    gets(up_down);

    if (up_down[0] == '1') {
        for (n = length - 1; n > 0; n--) {
            tmp1 = first;
            tmp2 = &((*first)->next_homework);
            for (i = 0; i < n; i++) {
                flag = 0;
                printf("0");
                switch (buffer[0]) {
                    case '1':   //if ((*tmp)->ID > (*tmp)->next_homework->ID) flag = 1;
                                if ((**tmp1).ID > (**tmp2).ID) flag = 1;
                                printf("1");
                                break;

                    case '2':   //if (strcmp((*tmp)->name, (*tmp)->next_homework->name) > 0) flag = 1;
                                if (strcmp((*tmp1)->name, (*tmp2)->name) > 0) flag = 1;
                                break;

                    case '3':   //if (strcmp((*tmp)->theme, (*tmp)->next_homework->theme) > 0) flag = 1;
                                if (strcmp((*tmp1)->theme, (*tmp2)->theme) > 0) flag = 1;
                                break;

                    case '4':   //if ((*tmp)->bonus_work > (*tmp)->next_homework->bonus_work) flag = 1;
                                if ((*tmp1)->bonus_work > (*tmp2)->bonus_work) flag = 1;
                                break;

                    case '5':   //if ((*tmp)->main_part_difficulty > (*tmp)->next_homework->main_part_difficulty) flag = 1;
                                if ((*tmp1)->main_part_difficulty > (*tmp2)->main_part_difficulty) flag = 1;
                                break;

                    case '6':   //if ((*tmp)->bonus_difficulty > (*tmp)->next_homework->bonus_difficulty) flag = 1;
                                if ((*tmp1)->bonus_difficulty > (*tmp2)->bonus_difficulty) flag = 1;
                                break;
                }
                if (flag) {

                    //if (*tmp1 == *first) *first = *tmp2;
                    //if (*tmp2 == *last) *last = *tmp1;
                    printf("2");
                    if (tmp1 == first) *first = *tmp2;
                    if (tmp2 == last) *last = *tmp1;
                    printf("3");

                    change_two_pointers(&((*tmp1)->next_homework), &((*tmp2)->next_homework));
                    change_two_pointers(tmp1, tmp2);
                    printf("4");


                /*
                    one = (*tmp)->next_homework;
                    two = (*tmp);

                    one->next_homework = (*tmp);
                    two->next_homework = (*tmp)->next_homework->next_homework;

                    if (tmp == first) *first = one;
                    if (tmp == last) *last = two;           //tento a dalsi radek udelaji to same
                    //if ((*tmp)->next_homework == *last) *last = two;

                    if ((*tmp) == *first) *first = one;
                    if ((*tmp)->next_homework == *last) *last = two;

                    tmp = &one;
                */
                    /*
                    help = *tmp;
                    *tmp = (*tmp)->next_homework;
                    (*tmp)->next_homework = help;
                    */

                    /*
                    int *tmp = *pptra;
                    *pptra = *pptrb;
                    *pptrb = tmp;

                    help = *ptmp;
                    *ptmp = tmp->next_homework;
                    tmp->next_homework = help;

                    change(&tmp, &(tmp->next_homework));

                    tmp->
                    */

                    /*
                    one = tmp->next_homework;
                    two = tmp;

                    //two->next_homework = one->next_homework;
                    one->next_homework = two;
                    two->next_homework = tmp->next_homework->next_homework;

                    if (tmp == homeworks.first) homeworks.first = one;
                    if (tmp->next_homework == homeworks.last) homeworks.last = two;

                    tmp = one;
                    */
                    //tmp->next_homework = two;
                    //continue;
                }
                tmp1 = tmp2;
                tmp2 = &((*tmp2)->next_homework);
                //(*tmp) = (*tmp)->next_homework;
                printf("5");
            }
        }
    } /*else {

    }*/

    printf("%s\t%s\t%s\t%s\t%s", (*tmp1)->name, (*first)->name, (*first)->next_homework->name, (*first)->next_homework->next_homework->name, (*first)->next_homework->next_homework->next_homework->name);
    getchar();
/*
    t_database homeworks;
    homeworks.first = *first;
    homeworks.last = *last;
    return homeworks;
    */
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
change_two_next_values(&((*one)->next_homework), &((*two)->next_homework));
void change_two_next_values(t_homework **one, t_homework **two) {

}
*/


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void save_to_csv(t_database homeworks) {
    char output_file_name[20] = {0};
    printf("\n\n%20cJak se ma soubor jmenovat? (Jmeno souboru zadejte ve tvaru \"nazev\".csv)", '\0');
    printf("\n\n%20c", '\0');
    gets(output_file_name);

    FILE *output_file = fopen(output_file_name,"w");
    t_homework* homework = homeworks.first;

    while(homework != homeworks.last) {
        fprintf(output_file,"%d;%s;%s;%d;%d;%d\n", homework->ID, homework->name, homework->theme, homework->bonus_work, homework->main_part_difficulty, homework->bonus_difficulty);
        homework = homework->next_homework;
    }
    fprintf(output_file,"%d;%s;%s;%d;%d;%d\n", homework->ID, homework->name, homework->theme, homework->bonus_work, homework->main_part_difficulty, homework->bonus_difficulty);
    fclose(output_file);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void clear_and_end(t_database homeworks) {
    t_homework* tmp = homeworks.first;
    t_homework* temp;

    while (tmp != homeworks.last) {
        temp = tmp->next_homework;
        free(tmp);
        tmp = temp;
    }
    free(tmp);
}
