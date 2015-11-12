#include <stdio.h>
#include <string.h>
#include <tre/tre.h>

int regex(char *reg, char* str) {
    int result=1;

    unsigned n;

    regex_t pb;
    regmatch_t pmatch[16];

    /* Match the regex */

    if (tre_regcomp(&pb, reg, REG_EXTENDED | REG_ICASE) == REG_OK) {
        result = tre_regexec(&pb, str, 16, pmatch, 0);
        tre_regfree(&pb);
        for(n=0; n<16 && pmatch[n].rm_so != -1; n++) {
            printf("%d: %d<->%d\n", n, pmatch[n].rm_so, pmatch[n].rm_eo);
            // Store the strings for BennuGD use
        }
    }

    if(result == 0) {
        return pmatch[0].rm_so;
    } else {
        return -1;
    }
}

int split(char *reg, char *str) {
    int result=1;
    
    unsigned n;
    
    regex_t pb;
    regmatch_t pmatch[16];
    
    /* Match the regex */
    
    if (tre_regcomp(&pb, reg, REG_EXTENDED | REG_ICASE) == REG_OK) {
        result = tre_regexec(&pb, str, 16, pmatch, 0);
        tre_regfree(&pb);
        for(n=0; n<16 && pmatch[n].rm_so != -1; n++) {
            printf("%d: %d<->%d\n", n, pmatch[n].rm_so, pmatch[n].rm_eo);
            // Store the strings for BennuGD use
        }
    }
    
    if(result == 0) {
        return pmatch[0].rm_so;
    } else {
        return -1;
    }
}

int main(int argc, char *argv[]) {
    // Test for regex function
    char *str = "It's raining cat's and dogs";
    char *reg = "cat";

    printf("match found at %d\n", regex(reg, str));
    printf("%d is the last character position in 99 bottles of "
           "beer on the wall\n",
           regex("$","99 bottles of beer on the wall."));
    
    // Test for split function
    str = "A,B,C,D,E";
    split(",", str);
    
    return 0;
}
