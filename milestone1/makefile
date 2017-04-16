# 3420ICT System Programming
# SID: S2193948
# Name: Chun Hung Wong (Grimes)
# Program: makefile
# Purpose: Simplify the works of compile time


# Assign Value to an variable
CC = clang			#clang or gcc compiler

# Main Functions
all: sync #all = "target", default functions of sync & clean

# Print out the "Hello, world"
sync: sync.c
	$(CC) -Wall -std=c11 -o bin/sync sync.c

 # 	clang -Wall -std=c11 -o Hello Hello.c # Original command
 # 	$(CC) -Wall -std=c11 -o hello hello.c && mv hello ./bin
 # best practice for put the correct path and folder

# Clean up the object and executive files
clean:
	rm bin/*
