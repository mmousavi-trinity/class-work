//OMH: I recieved help on this from a peer

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_COUNT 100


void print(int a[], int size) {
        int i;
        for ( i=0; i < size; ++i) {
                printf("%d\n", a[i]);
        }
}
int find_out_of_order(int a[], int size) {
       int i,j;
        for ( i = 0; i < size-1; ++i) {
                if (a[i] > a[i+1]) {
                        return i;
}
else{
        int tmp;
        for (i = 0; i < size-1; i++){
         for ( j = 0; j < size-1-i; j++){
         if(a[j] > a[j+1]){

                tmp = a[j];
                a[j] = a[j+1];
                a[j+1] = tmp;
         }
        }

   }
  }
}
return -1;
}



int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("usage:  %s infile outfile\n", argv[0]);
        return 1;
    }
    FILE * instream = fopen(argv[1], "r");
    if (instream == NULL) {
        printf("can't open file %s\n", argv[1]);
        return 1;
    }
    FILE * outstream = fopen(argv[2], "w");
    if (outstream == NULL) {
        printf("can't open file %s\n", argv[2]);
        return 1;
    }
    int unsort_arr[MAX_COUNT];
    int ch;
        int cnt = 0;
    while ((ch = fgetc(instream)) != EOF) {
        char *tempStr;
        tempStr = (char *) malloc(15);
        if (!isdigit(ch)) {
            printf("improper data in file %s\n", argv[1]); 
            return 1;
        }
        else {
            while (isdigit(ch)){
                char c = ch;
                char str[2] = {c , '\0'};
                char tempCh[25] = "";
                strcpy(tempCh,str);
                strcat(tempStr, tempCh);
                if ((ch = fgetc(instream)) == EOF){
                    break;
                }
                else if ((!isdigit(ch))) {
                    if ((ch!=32) && (ch!=48) && (ch!=10)){
                        printf("improper data in file %s\n", argv[1]);
                        return 1;
                    }
                }
            }
            ch = atoi(tempStr);
            unsort_arr[cnt] = ch;
            cnt++;
            free(tempStr);
        }
    }
    if ((cnt < 1) || (cnt > MAX_COUNT)) {
        printf(" Number of values must be between 1 and %d\n", MAX_COUNT);
        return EXIT_FAILURE;
    }
    find_out_of_order(unsort_arr, cnt);
    char * sorted_arr;
    sorted_arr = malloc(cnt*2);
    char space[2] = "\n";
    int h;
    for (h=0; h<cnt; h++) {
        char hold[30];
        int value = unsort_arr[h];
        sprintf(hold, "%d", value);
        strcat(hold, space);
        if (h==0){
            strcpy(sorted_arr, hold);
        }
        else {
            strcat(sorted_arr, hold);
        }
    }

    int w = 0;
    while((ch = sorted_arr[w]) != '\0' ) {
        fputc(ch, outstream);
        w++;
    }
    int out_of_order = find_out_of_order(unsort_arr, cnt);
    if (out_of_order < 0) {
        printf("sorted\n");
    }
    else {
        printf("not sorted\n");
        printf("first out-of-order element at index %d\n", out_of_order);
    }

    fclose(instream);
    fclose(outstream);
    return EXIT_SUCCESS;
}


