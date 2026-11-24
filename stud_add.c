#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

/* Smallest positive roll number not used by any node */
static int next_roll(void)
{
    int r = 1;
    while (find_by_roll(r)) r++;
    return r;
}

void stud_add(void)
{
    Student *n = (Student *)malloc(sizeof(Student));
    Student *p;
    if (!n) { printf("Memory allocation failed.\n"); return; }

    n->roll = next_roll();
    do {
        printf("Enter Student Name: ");
        read_line(n->name, NAME_LEN);
        if (n->name[0] == '\0') printf("Name cannot be empty.\n");
    } while (n->name[0] == '\0');
    n->percentage = read_percentage();
    n->next = NULL;

    if (!head) head = n;
    else {
        for (p = head; p->next; p = p->next) ;
        p->next = n;
    }
    printf("Record added. Roll Number assigned: %d\n", n->roll);
}
