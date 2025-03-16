
# Group Number:18
# -------------Group Member Names and ID-------------
# 1]Swapnil Yadav     2021B3A72770P
# 2]Manav Pahwa       2021B5A72796P
# 3]Ishan Wani        2021B3A72772P
# 4]Pratyaksh Kansal  2021B4A72783P
# 5]Atharv Joshi      2021B4A72749P
# ---------------------------------------------------

# This file uses GNU make utility, which determines automatically which pieces of a large program need to be recompiled, and issues the commands to recompile them. The correctness of your make file depends on file dependencies used correctly.

stage1exe: driver.o parser.o lexer.o stack.o parseTree.o
	gcc -o stage1exe driver.o parser.o lexer.o stack.o parseTree.o

driver.o: driver.c
	gcc -c driver.c

parser: parser.o lexer.o stack.o parseTree.o
	gcc -o parser1exe parser.o lexer.o stack.o parseTree.o
	./parser1exe $(source_code) grammar.txt

parser.o: parser.c
	gcc -c parser.c

stack.o: stack.c
	gcc -c stack.c 

parseTree.o: parseTree.c
	gcc -c parseTree.c

lexer: lexer.o
	gcc -o lexer1exe lexer.o
	./lexer1exe $(source_code)

lexer.o: lexer.c
	gcc -c lexer.c

clean:
	rm *.o
	rm *1exe
	clear