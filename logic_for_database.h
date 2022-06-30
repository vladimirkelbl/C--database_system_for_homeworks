#ifndef LOGIC_FOR_DATABASE_H_INCLUDED
#define LOGIC_FOR_DATABASE_H_INCLUDED

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

t_database read_from_csv(char* str);
t_database init();
void show_database(t_database homeworks);
t_database add_item(t_database homeworks);
t_database append_csv(t_database homeworks);
t_database delete_item(t_database homeworks);
void change_two_pointers(t_homework **one, t_homework **two);
//t_database sort_homeworks(t_homework **first, t_homework **last);
void sort_homeworks(t_homework **first, t_homework **last);
void save_to_csv(t_database homeworks);
void clear_and_end(t_database homeworks);

#endif // LOGIC_FOR_DATABASE_H_INCLUDED
