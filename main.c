#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "student.h"

Student *head = NULL;

/* ---------- input helpers ---------- */
void read_line(char *buf, int size)
{
    if (!fgets(buf, size, stdin)) { buf[0] = '\0'; return; }
    size_t n = strlen(buf);
    if (n > 0 && buf[n - 1] == '\n') buf[n - 1] = '\0';
    else { int c; while ((c = getchar()) != '\n' && c != EOF) ; } /* discard overflow */
}

char read_choice(void)
{
    char buf[64];
    read_line(buf, sizeof buf);
    return buf[0] ? (char)tolower((unsigned char)buf[0]) : '\0';
}

int read_int(void)
{
    char buf[64], *end;
    long v;
    read_line(buf, sizeof buf);
    v = strtol(buf, &end, 10);
    if (end == buf) return -1;
    return (int)v;
}

float read_percentage(void)
{
    char buf[64], *end;
    float v;
    for (;;) {
        printf("Enter Percentage (0-100): ");
        read_line(buf, sizeof buf);
        v = strtof(buf, &end);
        if (end != buf && *end == '\0' && v >= 0.0f && v <= 100.0f) return v;
        printf("Invalid percentage. Try again.\n");
    }
}

/* case-insensitive substring search */
int ci_contains(const char *text, const char *pat)
{
    size_t tl = strlen(text), pl = strlen(pat), i, j;
    if (pl == 0) return 1;
    for (i = 0; i + pl <= tl; i++) {
        for (j = 0; j < pl; j++)
            if (tolower((unsigned char)text[i + j]) != tolower((unsigned char)pat[j])) break;
        if (j == pl) return 1;
    }
    return 0;
}

/* ---------- display helpers ---------- */
void print_header(void)
{
    printf("--------------------------------------\n");
    printf("%-8s %-20s %s\n", "Roll No", "Name", "Percentage");
    printf("--------------------------------------\n");
}

void print_row(const Student *s)
{
    printf("%-8d %-20s %.1f\n", s->roll, s->name, s->percentage);
}

Student *find_by_roll(int roll)
{
    Student *p;
    for (p = head; p; p = p->next)
        if (p->roll == roll) return p;
    return NULL;
}

void free_list(void)
{
    Student *p;
    while (head) { p = head; head = head->next; free(p); }
}

/* ---------- menu ---------- */
static void show_menu(void)
{
    printf("\n**** STUDENT RECORD MENU ****\n\n");
    printf("A/a : Add New Record\n");
    printf("D/d : Delete a Record\n");
    printf("S/s : Show the List\n");
    printf("M/m : Modify a Record\n");
    printf("V/v : Save\n");
    printf("T/t : Sort the List\n");
    printf("E/e : Exit\n\n");
    printf("Enter Your Choice: ");
}

static int do_exit(void)   /* returns 1 if program should quit */
{
    for (;;) {
        printf("\nS/s : Save and Exit\n");
        printf("E/e : Exit Without Saving\n\n");
        printf("Enter Your Choice: ");
        char c = read_choice();
        if (c == 's') { stud_save(); return 1; }
        if (c == 'e') return 1;
        printf("Invalid choice.\n");
    }
}

int main(void)
{
    stud_load();
    for (;;) {
        show_menu();
        switch (read_choice()) {
            case 'a': stud_add();  break;
            case 'd': stud_del();  break;
            case 's': stud_show(); break;
            case 'm': stud_mod();  break;
            case 'v': stud_save(); break;
            case 't': stud_sort(); break;
            case 'e': if (do_exit()) { free_list(); return 0; } break;
            default:  printf("Invalid choice. Please try again.\n");
        }
    }
}
