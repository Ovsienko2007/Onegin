#ifndef FILE_READ_H_
#define FILE_READ_H_

#include <assert.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "my_string_functions.h"

/**
 * @brief reads all lines from file write number of lines in text_len
 * 
 * @param [in]   file_name  name of file
 * @param [out]  text_len   number of lines in file
 * 
 * @return string with lines from file, NULL in case of error
 */
char * read_file(const char * file_name, int * text_len);

/**
 * @brief finds the size of the given file in bytes
 * 
 * @param [in]   file_name  name of file
 * 
 * @return  size of the given file
 */
unsigned int find_file_size(const char * file_name);

/**
 * @brief finds the number of lines in the given text
 * 
 * @param [in]   text  text
 * 
 * @return  the number of lines in the given text, 0 in case of error
 */
int find_len_text_lines(const char * text);

/**
 * @brief replaces the first line_count enters of text with \0
 * 
 * @param [out]  text        text
 * @param [in]   line_count  number of lines
 * 
 * @return  array of pointers to the first elements of the rows, NULL in case of error
 */
char ** split_text(char * text, int line_count);
#endif