#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

/* On disk each record is: int roll, char name[NAME_LEN], float percentage */

void stud_save(void)
{
    FILE *fp = fopen(DATA_FILE, "wb");
    Student *p;
    int count = 0;
    if (!fp) { perror("Cannot open " DATA_FILE " for writing"); return; }
    for (p = head; p; p = p->next) {
        if (fwrite(&p->roll, sizeof p->roll, 1, fp) != 1 ||
            fwrite(p->name, NAME_LEN, 1, fp) != 1 ||
            fwrite(&p->percentage, sizeof p->percentage, 1, fp) != 1) {
            printf("Error while writing to " DATA_FILE ".\n");
            fclose(fp);
            return;
        }
        count++;
    }
    fclose(fp);
    printf("%d record(s) saved to " DATA_FILE ".\n", count);
}

void stud_load(void)
{
    FILE *fp = fopen(DATA_FILE, "rb");
    Student *tail = NULL, *n;
    int count = 0;
    if (!fp) return;   /* first run: no file yet */

    for (;;) {
        n = (Student *)malloc(sizeof(Student));
        if (!n) break;
        if (fread(&n->roll, sizeof n->roll, 1, fp) != 1 ||
            fread(n->name, NAME_LEN, 1, fp) != 1 ||
            fread(&n->percentage, sizeof n->percentage, 1, fp) != 1) {
            free(n);
            break;
        }
        n->name[NAME_LEN - 1] = '\0';
        n->next = NULL;
        if (tail) tail->next = n; else head = n;
        tail = n;
        count++;
    }
    fclose(fp);
    if (count) printf("Loaded %d record(s) from " DATA_FILE ".\n", count);
}
