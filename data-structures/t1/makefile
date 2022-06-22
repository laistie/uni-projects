# COMPILER
CC = gcc

# COMPILER FLAGS
CFLAGS = -Wall -fstack-protector-all -g -std=c99

# PROGRAM NAME
PROGRAM = ted

# .c FILES
sources := $(wildcard *.c)

# .h FILES
headers := $(wildcard *.h)

# .o FILES
objects := $(wildcard *.o)

$(PROGRAM): $(sources) $(headers)
	$(CC) $(CFLAGS) $(sources) $(headers) -o $(PROGRAM)
	
clean:
	rm $(objects) $(PROGRAM)