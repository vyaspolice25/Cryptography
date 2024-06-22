#include <stdio.h>
#include <string.h>
#include <ctype.h>

void decryptPlayfair(char ciphertext[], char keyword[], char plaintext[]) {
    char matrix[5][5];
    int used[26] = {0};
    int klen = strlen(keyword);
    int kpos = 0;

    for (int i = 0; i < klen; i++) {
        if (!used[keyword[i] - 'A'] && keyword[i] != 'J') {
            matrix[kpos / 5][kpos % 5] = (keyword[i] == 'J') ? 'I' : keyword[i];
            used[keyword[i] - 'A'] = 1;
            kpos++;
        }
    }

    for (int i = 0; i < 26; i++) {
        if (i != ('J' - 'A') && !used[i]) {
            matrix[kpos / 5][kpos % 5] = 'A' + i;
            used[i] = 1;
            kpos++;
        }
    }

    int len = strlen(ciphertext);
    int pidx = 0;

    for (int i = 0; i < len; i += 2) {
        char a = toupper(ciphertext[i]);
        char b = toupper(ciphertext[i + 1]);

        if (a == b) {
            b = 'X'; 
            i--;  
        }

        int r1, c1, r2, c2;
       
        for (int r = 0; r < 5; r++) {
            for (int c = 0; c < 5; c++) {
                if (matrix[r][c] == a) {
                    r1 = r;
                    c1 = c;
                }
                if (matrix[r][c] == b) {
                    r2 = r;
                    c2 = c;
                }
            }
        }

        if (r1 == r2) {
            
            plaintext[pidx++] = matrix[r1][(c1 + 4) % 5];
            plaintext[pidx++] = matrix[r2][(c2 + 4) % 5];
        } else if (c1 == c2) {
          
            plaintext[pidx++] = matrix[(r1 + 4) % 5][c1];
            plaintext[pidx++] = matrix[(r2 + 4) % 5][c2];
        } else {
           
            plaintext[pidx++] = matrix[r1][c2];
            plaintext[pidx++] = matrix[r2][c1];
        }
    }
    plaintext[pidx] = '\0';
}

int main() {
    char ciphertext[] = "KXJEY UREBE ZWEHE WRYTU HEYFS KREHE GOYFI WTTTU OLKSY CAJPO BOTEI ZONTX BYBNT GONEY CUZWR GDSON SXBOU YWRHE BAAHY USEDQ";
    char keyword[] = "PLAYFAIR";

    char plaintext[1000];

    decryptPlayfair(ciphertext, keyword, plaintext);

    printf("Decrypted Message:\n%s\n", plaintext);

    return 0;
}

OUTPUT :

Decrypted Message:
xkhak apana masad eturi naiis eachi fyied tothi stvic llamo nthep ertex cauti ously andju mpedq
