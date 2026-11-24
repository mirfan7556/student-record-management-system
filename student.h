#ifndef STUDENT_H
#define STUDENT_H

#define NAME_LEN 50
#define DATA_FILE "student.dat"

typedef struct student {
    int roll;
    char name[NAME_LEN];
    float percentage;
    struct student *next;
} Student;

extern Student *head;   /* head of the singly linked list */

/* module functions */
void stud_add(void);
void stud_del(void);
void stud_show(void);
void stud_mod(void);
void stud_save(void);
void stud_load(void);
void stud_sort(void);

/* helpers (main.c) */
char read_choice(void);
void read_line(char *buf, int size);
float read_percentage(void);
int read_int(void);
int ci_contains(const char *text, const char *pat);
void print_header(void);
void print_row(const Student *s);
Student *find_by_roll(int roll);
void free_list(void);

#endif
