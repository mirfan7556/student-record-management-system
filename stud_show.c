#include <stdio.h>
#include "student.h"

void stud_show(void)
{
    Student *p;
    if (!head) { printf("\nNo records to display.\n"); return; }
    printf("\n");
    print_header();
    for (p = head; p; p = p->next) print_row(p);
    printf("--------------------------------------\n");
}
