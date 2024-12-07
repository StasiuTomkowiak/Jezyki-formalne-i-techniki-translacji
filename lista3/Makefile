FLAGS = -W -O3

.PHONY = all clean cleanall

all: calculator

calculator:calculator.y calculator.l
	bison -o calculator_y.c -d calculator.y
	flex -o calculator_l.c calculator.l
	$(CC) $(FLAGS) -o calculator calculator_y.c calculator_l.c -lm

clean:
	rm -f *.c *.h

cleanall: clean
	rm -f calculator
