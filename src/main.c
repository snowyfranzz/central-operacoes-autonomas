#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <locale.h>
#include <ctype.h>

// ========== FUNCOES ==========

int isNumber(char c) {
    if (c >= 0x30 && c <= 0x39) {
        return 1;
    }

    return 0;
}

int isLetter(char c) {
    if (toupper(c) >= 0x41 && toupper(c) <= 0x5A) {
        return 1;
    }

    return 0;
}

void readString(char s[], int size) {
    printf("Escreva ate %d caracteres: ", size - 1);
    fgets(s, size, stdin);
    s[strcspn(s,"\n")] = '\0';
}

int verificar(char s[], int size) {
    int i = 0, success = 0;

    while (s[i] != '\0') {
        if (i <= 1) {
            if (isLetter(s[i])) {
                success++;
            }
        } else {
            if (isNumber(s[i])) {
                success++;
            }
        }
        i++;
    }

    if (success == size - 1) {
        return 1;
    }

    return 0;
}


// ========== STRUCTS ==========



// ========== MAIN ==========


int main() {
    char gok[5];
    int i, L = 0, N = 0;

    readString(gok, sizeof(gok));

    while (gok[i] != '\0') {
        if (isLetter(gok[i])) {
            L++;
        }
        if (isNumber(gok[i])) {
            N++;
        }

        i++;
    }

    printf("\n%d numbers\n%d letters", N, L);

    if (verificar(gok, sizeof(gok))) {
        printf("\n\nID Compativel");
    } else {
        printf("\n\nID Incompativel");
    }

    return 0;
}

int main(){
    return 0;
}