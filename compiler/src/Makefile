gcc = g++ -std=c++17 

all: compiler
compiler: 
	bison -d -o parser.c parser.y -Wcounterexamples
	flex -o lexer.c lexer.l
	$(gcc) lexer.c parser.c compiler.cpp ST.cpp -o kompilator
clean: 
	rm -f lexer.c lexer.o parser.c parser.h parser.o kompilator
