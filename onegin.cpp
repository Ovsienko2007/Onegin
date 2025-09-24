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
static void swap(void *par1, void *par2, size_t size) {
    char *char_par1 = (char*)par1;
    char *char_par2 = (char*)par2;
    
    for (size_t par_pos = 0; par_pos < size; par_pos++) {
        char buffer = char_par1[par_pos];
        char_par1[par_pos] = char_par2[par_pos];
        char_par2[par_pos] = buffer;
    }
}

static void * data_pos(const void* data, size_t size_elem, int position){
    return (void *)((size_t)data + size_elem * position);
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
static int partition_lomuto(const void *text, size_t elem,  int start, int end, compare_str_func func){
    void *base = data_pos(text, elem, end - 1);
    int new_base_pos = start;

    for (int text_line = start; text_line < end; text_line++){
        if (func(data_pos(text, elem, text_line), base) < 0){
            swap(data_pos(text, elem, new_base_pos), data_pos(text, elem, text_line), elem);
            new_base_pos++;
        }
    }
    swap(base, data_pos(text, elem, new_base_pos), elem);
    return new_base_pos;
}

static int partition_hoar(const void *text, size_t elem,  int start, int end, compare_str_func func){
    void *base = data_pos(text, elem, end - 1);
    int start_position = start;
    int end_position = end - 2;

    while (end_position >= start_position){
        while (start_position < end && func(data_pos(text, elem, start_position), base) < 0){
            start_position++;
        }
        while (end_position >  0 && func(data_pos(text, elem, end_position), base) > 0){
            end_position--;
        }

        
        if (start_position >=  end_position) break;

        swap(data_pos(text, elem, start_position), data_pos(text, elem, end_position), elem);

        start_position++;
        end_position--;
    }
    swap(base, data_pos(text, elem, start_position), elem);
    return start_position;
}


void my_qsort(const void *data, size_t elem, int start, int end, compare_str_func func){
    if (end - start <= 1 || start < 0) return;

    int smaller_elems = partition_hoar(data, elem,  start, end, func);
    my_qsort(data, elem, start, smaller_elems, func);
    my_qsort(data, elem, smaller_elems + 1, end, func);
}

int bubble_sort(void *text, size_t elem, int num_lines, compare_str_func func){
    bool cycle_status = true;
    while (cycle_status){
        cycle_status = false;

        for (int text_line = 0; text_line < num_lines - 1; text_line++){
            if (func(data_pos(text, elem, text_line), data_pos(text, elem, text_line + 1)) > 0){
                cycle_status = true;
                swap(data_pos(text, elem, text_line), data_pos(text, elem, text_line + 1), elem);
            }
        }
    }
    return 0;
}

int my_strcmp_for_sort(const void *param1, const void *param2){
    const char *str1 = *(const char * const *)param1;
    const char *str2 = *(const char * const *)param2;

    size_t n = 0;
    while (str1[n] != '\0' && str2[n] != '\0'){
        if (str1[n] != str2[n]){
            return str1[n] - str2[n];
        }
        n++;
    }
    return str1[n] - str2[n];
}

int my_strcmp_without_case(const void *param1, const void *param2){
    const char *str1 = *(const char * const *)param1;
    const char *str2 = *(const char * const *)param2;

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

int my_strrcmp_without_case(const void *param1, const void *param2){
    const char *str1 = *(const char * const *)param1;
    const char *str2 = *(const char * const *)param2;

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
    while (isalpha(str[str_pos]) == 0 || str[str_pos] == '\0'){
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