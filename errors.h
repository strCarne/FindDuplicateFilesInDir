#ifndef ERRORS_H
#define ERRORS_H

#define CLI_ARGS_ERROR_CODE 1
#define INTERNAL_ERROR_CODE 2

#define ERROR_CLI_ARGS "err: cli args are not defined or incorrect\n<arg_1>: directory_name\n<arg_2>: N1 (min_file_size)\n<arg3>: N2 (max_file_size)\nSize must be defined in bytes\n"
#define ERROR_N1_IS_NOT_A_NUMBER "err: <arg_2> N1 (min_file_size) is not a number\n"
#define ERROR_N2_IS_NOT_A_NUMBER "err: <arg_3> N2 (max_file_size) is not a number\n"
#define ERROR_N1_N2 "err: N1 < 0 or N2 < 0 or N1 > N2\n"

#define ERROR_OPEN_DIR "err: directory with defined dir_name doesn't exist, is a file of there not enough rights\n"

#endif