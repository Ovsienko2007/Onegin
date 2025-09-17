#include <stdio.h>
#include "my_string_functions.h"
#include "onegin.h"

int main(){
    int text_size = 14;
    char ** text = (char **)calloc(text_size, sizeof(char *));

    FILE * file = fopen("text.txt", "r");

    text_size = read_file(file, &text_size, &text);

    if (file == NULL){
    	printf("File not found\n");
	return 0;
    }

    fclose(file);


    for (int i = 0; i < text_size; i++){
        printf("%s\n", text[i]);
    }
    printf("_____________________________\n");

    sort(&text, text_size, my_strcmp);

    for (int text_i = 0; text_i < text_size; text_i++){
        printf("%s\n", text[text_i]);
    }
    printf("_____________________________\n");


    return 0;
}
