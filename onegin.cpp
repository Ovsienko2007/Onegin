#include "onegin.h"

/**
 * @brief counts the number of same elements from two strings from 
 * the end skips initial and final non-alphabetic characters
 * 
 * @param [in]    str1       the first string
 * @param [in]    str2       the second string
 * 
 * @return  0 if strings are equal or number less than 0 if str1 < str2 
 *          number greater than 0 if str1 > str2 
 */
static int is_str_same(const char *str1, const char *str2);

/**
 * @brief find the position of the first alphabetic character in a string
 * 
 * @param [in]  str string
 * 
 * @return  the position of the first alphabetic character in a string
 */
static int skip_start_symbols(const char *str);

/**
 * @brief find the position of the first alphabetic character in a string from the end
 * 
 * @param [in]  str            string
 * @param [in]  str_pos        end of string position
 * @param [in]  str_end_pos    last checked string position
 * 
 * @return  find the position of the first alphabetic character in a string from the end
 */
static int skip_end_symbols(const char *str, int str_pos, int str_end_pos);

/**
 * @brief change upper letters to lower
 * 
 * @param [in] symbol letters
 * 
 * @return  lower letter
 */
static char change_upper_to_lower(const char symbol);

/**
 * @brief find the position of the last element of string
 * 
 * @param [in] str string
 * 
 * @return  position of the last element of string
 */
static int go_to_str_end(const char *str);

/**
 * @brief swap two lines
 * 
 * @param [in] line1 the first line
 * @param [in] line1 the second line
 */
static void swap(char **line1, char **line2){
    char * buffer = *line1;
    *line1 = *line2;
    *line2 = buffer;
    return;
}

/**
 * @brief splits lines from text by func
 * 
 * @param [out] text  text
 * @param [in]  start the number of first line
 * @param [in]  end   the number of last line
 * 
 * @return number of lines going earlier by func
 */
static int partition(char **text, int start, int end, compare_str_func func){
    char *base = text[end - 1];
    int new_base_pos = start;

    for (int text_line = start; text_line < end; text_line++){
        if (func(text[text_line], base) < 0){
            swap(&text[new_base_pos], &text[text_line]);
            new_base_pos++;
        }
    }
    swap(&text[end - 1], &text[new_base_pos]);
    return new_base_pos;
}

void my_qsort(char **text, int start, int end, compare_str_func func){
    if (end - start <= 1 || start < 0) return;

    int smaller_elems = partition(text, start, end, func);
    my_qsort(text, start, smaller_elems, func);
    my_qsort(text, smaller_elems + 1, end, func);
}

int sort_text(char **text, int num_lines, compare_str_func func){
    bool cycle_status = true;
    while (cycle_status){
        cycle_status = false;

        for (int text_line = 0; text_line < num_lines - 1; text_line++){
            if (func(text[text_line], text[text_line + 1]) > 0){
                cycle_status = true;
                swap(&text[text_line], &text[text_line + 1]);
            }
        }
    }
    return 0;
}

int my_strcmp_without_case(const char *str1, const char *str2){
    int str1_pos = skip_start_symbols(str1);
    int str2_pos = skip_start_symbols(str2);

    while (str1[str1_pos] != '\0' && str2[str2_pos] != '\0'){
        if (change_upper_to_lower(str1[str1_pos]) != change_upper_to_lower(str2[str2_pos])){
            return change_upper_to_lower(str1[str1_pos]) - change_upper_to_lower(str2[str2_pos]);
        }
        str2_pos++;
        str1_pos++;
    }
    return 0;
}

int my_strrcmp_without_case(const char *str1, const char *str2){
    int str1_left_pos = skip_start_symbols(str1);
    int str2_left_pos = skip_start_symbols(str2);
     
    int str1_pos = go_to_str_end(str1) - 1;
    int str2_pos = go_to_str_end(str2) - 1;

    str1_pos = skip_end_symbols(str1, str1_pos, str1_left_pos);
    str2_pos = skip_end_symbols(str2, str2_pos, str2_left_pos);

    while (str1_left_pos <= str1_pos && str2_left_pos <= str2_pos){
        if (change_upper_to_lower(str1[str1_pos]) != change_upper_to_lower(str2[str2_pos])){
            return change_upper_to_lower(str1[str1_pos]) - change_upper_to_lower(str2[str2_pos]);
        }
        str2_pos--;
        str1_pos--;
    }

    return change_upper_to_lower(str1[str1_pos]) - change_upper_to_lower(str2[str2_pos]);
}

void print_text(char **text, int text_line_len){
    for (int text_line = 0; text_line < text_line_len; text_line++){
        printf("%4d: \"%s\"\n", text_line, text[text_line]);
    }
    printf("_____________________________\n");
}

int generate_random_text(char **text, int text_len, int gen_len){
    bool need_last_line = (gen_len % 2 == 1);

    gen_len /= 2;

    for (int line = 0; line < gen_len; line++){
        int spread = 10;
        
        int position = rand();
        
        position = position % (text_len - 2 * spread) + spread;

        int new_placement = -spread;
        int placement = -spread;
        
        while (new_placement < spread){
            new_placement++;

            if (abs(3 - is_str_same(text[position], text[position + new_placement])) < 
                abs(3 - is_str_same(text[position], text[position + placement])) && position != new_placement){
                placement = new_placement;
            }
        }
        printf("%s\n%s\n\n", text[position], text[position + placement]);
    }

    if (need_last_line){
        int position = rand();
        position = position % (text_len);
        printf("%s\n", text[position]);
    }

    return 0;
}

static int skip_start_symbols(const char *str){
    int str_pos = 0;
    while (isalpha(str[str_pos]) == 0 && str[str_pos] == '\0'){
        str_pos++;
    }

    return str_pos;
}

static int skip_end_symbols(const char *str, int str_pos, int str_end_pos){
    while (isalpha(str[str_pos]) == 0 && str_pos > str_end_pos){
        str_pos--;
    }

    return str_pos;
}

static int go_to_str_end(const char *str){
    int str_pos = 0;
    while (str[str_pos] != '\0'){
        str_pos++;
    }

    return str_pos;
}

static char change_upper_to_lower(const char symbol){
    if (isupper(symbol)){
        return symbol - 'A' + 'a';
    }

    return symbol;
}

static int is_str_same(const char *str1, const char *str2){
    int str1_left_pos = skip_start_symbols(str1);
    int str2_left_pos = skip_start_symbols(str2);
     
    int str1_pos = go_to_str_end(str1) - 1;
    int str2_pos = go_to_str_end(str2) - 1;

    str1_pos = skip_end_symbols(str1, str1_pos, str1_left_pos);
    str2_pos = skip_end_symbols(str2, str2_pos, str2_left_pos);

    int ans = 0;

    while (str1_left_pos <= str1_pos && str2_left_pos <= str2_pos){
        if (change_upper_to_lower(str1[str1_pos]) != change_upper_to_lower(str2[str2_pos])){
            break;
        }
        ans++;
        str2_pos--;
        str1_pos--;
    }
    return ans;
}