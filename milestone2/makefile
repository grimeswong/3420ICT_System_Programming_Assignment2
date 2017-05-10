# 3420ICT System Programming
# SID: S2193948
# Name: Chun Hung Wong (Grimes)
# Program: makefile
# Purpose: Simplify the works of compile time


# Assign Value to an variable
CC = clang			#clang or gcc compiler

# Main Functions
all: sync sema		#all = "target", default functions of sync & clean

# Print out the "Hello, world"
sync: sync.c
	$(CC) -Wall -std=c11 -o bin/sync sync.c

# Function of semaphore
sema: sema.c
	$(CC) -Wall -std=c11 -o bin/sema sema.c

# Clean up the object and executive files
clean:
	rm bin/*
