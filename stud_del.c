#include <stdio.h>
#include <stdlib.h>
#include "student.h"

static void delete_roll(int roll)
{
    Student *cur = head, *prev = NULL;
    while (cur && cur->roll != roll) { prev = cur; cur = cur->next; }
    if (!cur) { printf("Roll number %d not found.\n", roll); return; }
    if (prev) prev->next = cur->next; else head = cur->next;
    free(cur);
    printf("Record with roll number %d deleted.\n", roll);
}

void stud_del(void)
{
    char c;
    if (!head) { printf("\nList is empty.\n"); return; }

    printf("\nR/r : Delete using Roll Number\n");
    printf("N/n : Delete using Name\n\n");
    printf("Enter Your Choice: ");
    c = read_choice();

    if (c == 'r') {
        printf("Enter Roll Number: ");
        delete_roll(read_int());
    } else if (c == 'n') {
        char name[NAME_LEN];
        Student *p;
        int found = 0;
        printf("Enter Name: ");
        read_line(name, NAME_LEN);
        for (p = head; p; p = p->next) {
            if (ci_contains(p->name, name)) {
                if (!found) { printf("\n"); print_header(); }
                print_row(p);
                found = 1;
            }
        }
        if (!found) { printf("No matching records.\n"); return; }
        printf("--------------------------------------\n");
        printf("Enter Roll Number to delete: ");
        delete_roll(read_int());
    } else {
        printf("Invalid choice.\n");
    }
}
