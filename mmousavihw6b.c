//OMH: I received help on this from a peer


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int rotate(int inchar, int positions_to_rotate) {
    char* lc_alphabet = "abcdefghijklmnopqrstuvwxyz";
    char* uc_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    int code;
    /* look for input character in list of lowercase chars */
    char* chck_lc_alphabet = strchr(lc_alphabet, inchar);
    char* chck_uc_alphabet = strchr(uc_alphabet, inchar);    
    if (chck_lc_alphabet != NULL) {
        /* lower-case character:  find rotated char in lc_alphabet */
        int position_in_alphabet = chck_lc_alphabet - lc_alphabet;
        int string_len = strlen(lc_alphabet); //24
        int rotate_clean = position_in_alphabet + positions_to_rotate;
        if (rotate_clean <= 25){
            code = inchar+positions_to_rotate;
        }
        else {
            int remainder = (inchar+positions_to_rotate)-string_len;
            code = lc_alphabet[remainder];
        }
    }
    if (chck_uc_alphabet != NULL) {
        int position_in_alphabet = chck_uc_alphabet - uc_alphabet;
        int string_len = strlen(uc_alphabet); //24
        int rotate_clean = position_in_alphabet + positions_to_rotate;
        if (rotate_clean <= 25){
            code = inchar+positions_to_rotate;
        }
        else {
            int tempNum = (position_in_alphabet+positions_to_rotate);
            int remainder = tempNum-string_len;
            code = uc_alphabet[remainder];
        }
    }
  /* 
         * YOUR CODE GOES HERE:
         * use lc_alphabet and positions_to_rotate to find new character
         *   and return it
         * strlen(lc_alphabet) may be helpful
         */
    return(code);
    /*
     * YOUR CODE GOES HERE:
     * do something similar to the above for uppercase characters
     * if input character not found in either "alphabet" just return it
     */
}


int main(int argc, char *argv[]) {  
    if (argc != 3) { 
        printf("usage:  %s infile outfile\n", argv[0]);
        return 1;
    }
    FILE * instream = fopen(argv[1], "r");
    if (instream == NULL) { 
        printf("cannot open file %s\n", argv[1]);
        return 1;
    }
    FILE * outstream = fopen(argv[2], "w");
    if (outstream == NULL) { 
        printf("cannot open file %s\n", argv[2]);
        return 1;
    }
    int ch;
        int cnt = 0;
    while ((ch = fgetc(instream)) != EOF) {
        if (isalpha(ch)){
            int rotated = rotate(ch, 1);
            fputc(rotated, outstream);
        }
        else{
            fputc(ch, outstream);
        }
        cnt += 1;
    }
    fprintf(stderr, "%d characters echoed\n", cnt);
    fclose(instream);
    fclose(outstream);
    return 0;

}