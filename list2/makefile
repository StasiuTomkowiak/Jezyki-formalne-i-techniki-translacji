OUTPUT = zad1 zad2 zad3 zad4
SOURCES = zad1.l ex-2.l ex-3.l ex-4.l

all: zad1 zad2 zad3 zad4

zad1: 
	flex -ozad1.c zad1.l 
	gcc zad1.c -o zad1

zad2: 
	flex -ozad2.c zad2.l 
	gcc zad2.c -o zad2

zad3: 
	flex -ozad3.c zad3.l 
	gcc zad3.c -o zad3

zad4: 
	flex -ozad4.c zad4.l 
	gcc zad4.c -o zad4 -lm

zad1_test:
	./zad1 < test1a.txt

zad2_test:
	./zad2 < test2.adb

zad3_test_false:
	./zad3 < test3.cpp

zad3_test_true:
	./zad3 < test3.cpp a

zad4_test:
	./zad4


clean:
	rm -rf *.o *.c $(OUTPUT)