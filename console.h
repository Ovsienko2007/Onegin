#ifndef CONSOL_H_
#define CONSOL_H_

#include <stdio.h>

#include "my_string_functions.h"
#include "onegin.h"
#include "file_read.h"

#define CONSOLE_RED        "\033[31m"
#define CONSOLE_GREEN      "\033[32m"
#define CONSOLE_BLUE       "\033[34m"
#define CONSOLE_PIRPLE     "\033[35m"
#define CONSOLE_RESET      "\033[39m"

/**
 * @brief limits the length of a file name
 */
const int max_len = 101;

/**
 * @brief  start console
 * 
 * @return 0
 */
int run_console();

#endif