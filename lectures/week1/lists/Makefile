# COMP2521 20T2 ... Lab 01 Makefile

CC	= 2521 3c
CC	= gcc

.PHONY: all
all: useIntList randList

useIntList:	useIntList.o IntList.o
useIntList.o:	useIntList.c IntList.h
IntList.o:	IntList.c IntList.h

randList:	randList.o

.PHONY: clean
clean:
	-rm -f useIntList IntList.o useIntList.o
	-rm -f randList randList.o
