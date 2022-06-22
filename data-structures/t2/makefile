# COMPILER
CC = gcc

# COMPILER FLAGS
CFLAGS = -Wall -fstack-protector-all -g -std=c99 -lm

# PROGRAM NAME
PROGRAM = ted

# .c FILES
sources := $(wildcard *.c)

# .h FILES
headers := $(wildcard *.h)

# .o FILES
objects := $(wildcard *.o)

$(PROGRAM): $(sources) $(headers)
	$(CC) $(sources) $(headers) $(CFLAGS) -o $(PROGRAM)
	
clean:
	rm $(objects) $(PROGRAM)