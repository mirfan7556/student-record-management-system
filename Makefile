CC     = gcc
CFLAGS = -Wall -Wextra -std=c99 -D_POSIX_C_SOURCE=200809L
OBJS   = main.o stud_add.o stud_del.o stud_show.o stud_mod.o stud_save.o stud_sort.o

student: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -lm

%.o: %.c student.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) student
