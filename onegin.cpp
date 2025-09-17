#include "onegin.h"

// TODO use typedef for function pointers

int sort(char **str, int num_element, int (*func)(const char *, const char*)){
    bool x = true; // TODO rename
    while (x){
        x = false;

        for (int i = 0; i < num_element - 1; i++){ // TODO rename i
            if (func(str[i], str[i + 1]) > 0){
                x = true;
                char * l = str[i]; // TODO rename l
                str[i] = str[i + 1];
                str[i + 1] = l;
            }
        }
    }
    return 0;
}


