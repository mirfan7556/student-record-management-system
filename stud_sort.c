#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "student.h"

static int cmp_name(const Student *a, const Student *b)
{
    const char *x = a->name, *y = b->name;
    while (*x && *y && tolower((unsigned char)*x) == tolower((unsigned char)*y)) { x++; y++; }
    return tolower((unsigned char)*x) - tolower((unsigned char)*y);
}

static int cmp_pct(const Student *a, const Student *b)
{
    if (a->percentage < b->percentage) return -1;
    if (a->percentage > b->percentage) return 1;
    return 0;
}

/* Stable insertion sort that relinks nodes */
static void sort_list(int (*cmp)(const Student *, const Student *), int descending)
{
    Student *sorted = NULL, *cur = head, *next, **pp;
    while (cur) {
        next = cur->next;
        pp = &sorted;
        while (*pp) {
            int r = cmp(*pp, cur);
            if (descending ? (r >= 0) : (r <= 0)) pp = &(*pp)->next;
            else break;
        }
        cur->next = *pp;
        *pp = cur;
        cur = next;
    }
    head = sorted;
}

void stud_sort(void)
{
    char c;
    if (!head) { printf("\nList is empty.\n"); return; }

    printf("\nN/n : Sort by Name\n");
    printf("P/p : Sort by Percentage\n\n");
    printf("Enter Your Choice: ");
    c = read_choice();

    if (c == 'n') {
        sort_list(cmp_name, 0);
        printf("List sorted by name (A-Z).\n");
    } else if (c == 'p') {
        sort_list(cmp_pct, 1);
        printf("List sorted by percentage (highest first).\n");
    } else {
        printf("Invalid choice.\n");
    }
}
