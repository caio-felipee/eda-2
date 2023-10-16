// Comparison between two strings

#include <stdio.h>
#include <stdbool.h>

bool is_equal(char *str1, char *str2) {
    int i;
    for(i = 0; str1[i] != 0 && str2[i] != 0; i++) {
        if(str1[i] != str2[i])
            return false;
    }

    return str1[i] == str2[i];
}