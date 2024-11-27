#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ComputePrefixFunction(char *pat, int M, int *pi) {
    pi[1] = 0;
    int k = 0;
    for (int q = 2; q <=M; q++) {
        while (k > 0 && pat[k+1] != pat[q]) {
            k = pi[k];
        }
        if (pat[k+1] == pat[q]) {
            k = k + 1;
        }
        pi[q] = k;
    }
}

void KMPMatcher(char *pat, char *txt) {
    int N = strlen(txt);
    int M = strlen(pat);

    int pi[M+1];
    ComputePrefixFunction(pat, M, pi); 

    int q = 0;  

    for (int i = 0; i < N; i++) { 
        while (q > 0 && pat[q] != txt[i]) {  
            q = pi[q - 1];  
        }

        if (pat[q] == txt[i]) {
            q++;
        }

        if (q == M) {
            printf("Pattern found at index %d\n", i - M + 1);
            q = pi[q - 1];  // Prepare for the next potential match
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

    KMPMatcher(pat, text);

    free(text);

    return 0;
}