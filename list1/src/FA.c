#include <stdlib.h>
#include<stdio.h> 
#include<string.h> 
#include <math.h>

#define NO_OF_CHARS 26


int isSuffix(char *pat, int q, int k, char a) {
    if (pat[k-1] != a)
        return 0;
    for (int i = k - 1; i > 0; i--) {
        if (pat[i - 1] != pat[q - k + i])
            return 0;
    }
    return 1;
}

void computeTransitionFunction(char *pat, int M, int TF[][NO_OF_CHARS]) {
    int q, a, k;

    for (q = 0; q <= M; ++q) {
        for (a = 0; a < NO_OF_CHARS; ++a) {
            k = fmin(M + 1, q + 2);
            do {
                k = k - 1;  
            } while (k > 0 && !isSuffix(pat, q, k, 'a' + a));  
            
            TF[q][a] = k;
        }
    }
}
void FiniteAutomationMatcher(char *pat, char *txt) 
{ 
    int M = strlen(pat); 
    int N = strlen(txt); 
    int TF[M+1][NO_OF_CHARS]; 
  
    computeTransitionFunction(pat, M, TF); 

    int i, state=0; 
    for (i = 0; i < N; i++) 
    { 
            state = TF[state][txt[i]-'a'];
            if (state == M) {
                printf("\n Pattern found at index %d", i-M+1);
            }
    
    } 
} 
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <pattern> <filename>\n", argv[0]);
        return 1;
    }

    char *pat = argv[1];
    char *txt = argv[2];

    FILE *fp = fopen(txt, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    int txtLen = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *text = (char *)malloc(txtLen + 1);
    if (text == NULL) {
        printf("Error allocating memory.\n");
        return 1;
    }

    fread(text, 1, txtLen, fp);
    
    fclose(fp);
    text[txtLen] = '\0'; 

    FiniteAutomationMatcher(pat, text);

    free(text);

    return 0;
}