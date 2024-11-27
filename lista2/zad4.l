%option noyywrap

%{
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define ROZMIAR_STOSU 10

typedef struct {
    int dane[ROZMIAR_STOSU];
    int szczyt;
} Stos;

void inicjalizujStos(Stos *stos) {
    stos->szczyt = -1;
}

int czyPusty(Stos *stos) {
    return stos->szczyt == -1;
}

int czyPelny(Stos *stos) {
    return stos->szczyt == ROZMIAR_STOSU - 1;
}

void push(Stos *stos, int element) {
    if (czyPelny(stos)) {
        printf("Błąd: Przepełnienie stosu!\n");
        return;
    }
    stos->dane[++stos->szczyt] = element;
}

int pop(Stos *stos) {
    if (czyPusty(stos)) {
        printf("Błąd: Stos jest pusty!\n");
        return -1; // Zwrócenie wartości -1 jako sygnał błędu
    }
    return stos->dane[stos->szczyt--];
}
Stos stos;
int blad = 0;
%}

%%

-?[[:digit:]]+		      { push(&stos,atoi(yytext)); }

"+"             { 
                  if (stos.szczyt >= 1) { 
                      int b = pop(&stos);
                      int a = pop(&stos);
                      push(&stos,a + b);
                  } else {
                        printf("Błąd: za mała liczba argumentów\n");
                        blad = 1;
                  }
                }

"-"             { 
                  if (stos.szczyt >= 1) { 
                      int b = pop(&stos);
                      int a = pop(&stos);
                      push(&stos,a - b);
                  } else {
                        printf("Błąd: za mała liczba argumentów\n");
                        blad = 1;
                  }
                } 

"*"             { 
                  if (stos.szczyt >= 1) { 
                      int b = pop(&stos);
                      int a = pop(&stos);
                      push(&stos,a * b);
                  } else {
                        printf("Błąd: za mała liczba argumentów\n");
                        blad = 1;
                  }
                } 

"/"             { 
                  if (stos.szczyt >= 1) {
                        int b = pop(&stos);
                        int a = pop(&stos);
                        if (b == 0) {
                          printf("Błąd: Dzielenie calkowite przez zero\n");
                          blad = 1;  
                        } 
                        else {
                          push(&stos, a / b);
                      }
                  } else {   
                        printf("Błąd: za mała liczba argumentów\n");             
                        blad = 1;
                  }
                }   

"%"             { 
                  if (stos.szczyt >= 1) { 
                        int b = pop(&stos);
                        int a = pop(&stos);
                        if (b == 0) {
                          printf("Błąd: Dzielenie modulo przez zero\n");
                          blad = 1;  
                        } 
                        else {
                          push(&stos, a % b);
                      }
                  } else {  
                        printf("Błąd: za mała liczba argumentów\n");                    
                        blad = 1;
                  }
                }

"^"             { 
                  if (stos.szczyt >= 1) { 
                      int b = pop(&stos);
                      int a = pop(&stos);
                      push(&stos, (int)pow(a,b));
                  } else {
                      printf("Błąd: za mała liczba argumentów\n");
                      blad = 1;
                  }
                }   

[ \t]           {}

\n              { 
                  if (blad==1) {
                      blad = 0; 
                      inicjalizujStos(&stos);                      
                  } else if (stos.szczyt==0) {
                      int wynik = pop(&stos);
                      printf("= %d\n", wynik);
                  } else {
                      printf("Błąd: za mała liczba operatorów\n");
                  }
                }
.               { 
                  printf("Błąd: Nieznany znak '%s'\n", yytext); 
                  blad = 1; 
                }                           
%%

int main() {
   
    inicjalizujStos(&stos);
    while(true){
        yylex();
}
    return 0;
}
