#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "playfair.h"

int main () {
    char* encrypted = playfair_encrypt("tracts", "potxxxe");
    //puts(encrypted);
    char* decrypted = playfair_decrypt("typhus", "FV CF HH KI CQ CQ");
    //puts(decrypted);
    
    unsigned char* bit_encrypted = bit_encrypt("Hello world!");
    /*for(int i=0; i < 12;i++) {
        printf("%x ", bit_encrypted[i]);
        //80 9c 95 95 96 11 bc 96 b9 95 9d 10
    }*/

    char* bit_decrypted = bit_decrypt(bit_encrypted);
    //printf("|%s|", bit_decrypted);
    
    unsigned char* bmp_encrypted = bmp_encrypt("iuoafaee", "I play fair, but you cheating, aa bb xx cc");
    printf("|%s|\n", bmp_encrypted);
    char* bmp_decrypted = bmp_decrypt("iuoafaee", bmp_encrypted);
    printf("|%s|\n", bmp_decrypted);

    if (bmp_encrypted != NULL) free(bmp_encrypted);
    if (bmp_decrypted != NULL) free(bmp_decrypted);
    
    if (bit_decrypted != NULL) free(bit_decrypted);
    if (bit_encrypted != NULL) free(bit_encrypted);

    if (encrypted != NULL) free(encrypted);
    else puts("encrypted");
    
    if (decrypted != NULL) free(decrypted);
    else puts("decrypted");

    char* reversed = reverse("peremoga!");
    if (reversed != NULL) free(reversed);

    char* vig_encrypted = vigenere_encrypt("dd", NULL);
    if (vig_encrypted != NULL) free(vig_encrypted);

    char* vig_decrypted = vigenere_decrypt("peremoga", "zrada!");
    if (vig_decrypted != NULL) free(vig_decrypted);
}   
