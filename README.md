# idlemutithread

this repository contains a small demonstrattion of the use of pthreads in C/C++ code

it's meant to be used as a reference

I made this because most examples I found used a main thread that delegated tasks to threads created when they are needed and I wanted to try using a set number of threads

I may alter this to be able to decide on the number of threads on startup and/or do more than just print messages

this program can be compiled with gcc like this:

gcc main.c -pthread -o threads

it can be run like this:

./threads

alternatively a Makefile is provided, so it can be compiled and run like this:

make run

it can be checked for memory leaks with valgrind like this:

valgrind --leak-check=full ./threads

Valgrind is a flexible program for debugging and profiling Linux executables.
For more comprehensive information, please visit http://www.valgrind.org
