#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "student.h"

static void modify_node(Student *s)
{
    printf("\nN/n : Name\n");
    printf("P/p : Percentage\n\n");
    printf("Enter Your Choice: ");
    char c = read_choice();

    if (c == 'n') {
        char buf[NAME_LEN];
        printf("Enter New Name: ");
        read_line(buf, NAME_LEN);
        if (buf[0] == '\0') { printf("Name cannot be empty. No change made.\n"); return; }
        strcpy(s->name, buf);
        printf("Name updated.\n");
    } else if (c == 'p') {
        s->percentage = read_percentage();
        printf("Percentage updated.\n");
    } else {
        printf("Invalid choice.\n");
    }
}

void stud_mod(void)
{
    char c;
    Student *p, *target;
    if (!head) { printf("\nList is empty.\n"); return; }

    printf("\nR/r : Roll Number\n");
    printf("N/n : Name\n");
    printf("P/p : Percentage\n\n");
    printf("Enter Your Choice: ");
    c = read_choice();

    if (c == 'r') {
        printf("Enter Roll Number: ");
        target = find_by_roll(read_int());
        if (!target) { printf("Record not found.\n"); return; }
        modify_node(target);
    } else if (c == 'n' || c == 'p') {
        char name[NAME_LEN] = "";
        float pct = 0;
        int found = 0;
        if (c == 'n') { printf("Enter Name: "); read_line(name, NAME_LEN); }
        else pct = read_percentage();

        for (p = head; p; p = p->next) {
            int match = (c == 'n') ? ci_contains(p->name, name)
                                   : fabsf(p->percentage - pct) < 0.005f;
            if (match) {
                if (!found) { printf("\n"); print_header(); }
                print_row(p);
                found = 1;
            }
        }
        if (!found) { printf("No matching records.\n"); return; }
        printf("--------------------------------------\n");
        printf("Enter Roll Number to modify: ");
        target = find_by_roll(read_int());
        if (!target) { printf("Roll number not in the list.\n"); return; }
        modify_node(target);
    } else {
        printf("Invalid choice.\n");
    }
}
