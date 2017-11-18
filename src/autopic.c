#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <libgen.h>
#include <string.h>
#include <argcheck.h>


int main(int argc, char** argv)
{
	if (AreArgsValid(argc,argv) != 0) return 1;
	return 0;
}

CheckArgErrCode AreArgsValid(int arg_count,char** arg_buffer)
{
	if (IsArgCountValid(arg_count) == false) {printf("bad arguments count.Closing\n");return CHECK_INVALID_ARG_COUNT;}
	for (size_t arg_counter = 1; arg_counter < REQARGC; arg_counter++)
	{
		if (IsDirExists(arg_buffer[arg_counter]) == false) {printf("Directory \'%s\' does not exist. Closing\n",arg_buffer[arg_counter]); return CHECK_DIR_NOT_EXISTS;}
		if (IsDirEmpty(arg_buffer[arg_counter]) == false) {printf("Directory \'%s\' is not empty. Closing\n",arg_buffer[arg_counter]); return CHECK_DIR_NOT_EMPTY;}
	}
	if (AreDirNamesUnique(arg_buffer) == false){printf("Directories names are not unique. Closing\n"); return CHECK_DIRS_NAMES_NOT_UNIQUE;}
	return CHECK_OK;
}

static bool IsArgCountValid(int arg_count)
{
	if (arg_count != REQARGC) return false;
	return true;
}

static bool IsDirExists(char* dir_path)
{
	DIR* dir = opendir(dir_path);
	if (dir)
	{
		closedir(dir);
		return true;
	}
	return false;
}

static bool IsDirEmpty(char* dir_path)
{
	size_t file_counter = 0;
	DIR* dir = opendir(dir_path);
    if (dir)
    {
        while (readdir(dir) != NULL)
        	file_counter++;
        closedir(dir);
    }
    if (file_counter != 2) return false;
	return true;
}

static bool AreDirNamesUnique(char** dir_buffer)
{
	int dir_cmp_res,base_cmp_res;
	for (size_t buf_counter = 1; buf_counter < REQARGC; buf_counter++)
		for (size_t buf_counter2 = 1; buf_counter2 < REQARGC; buf_counter2++)
			if (buf_counter2 != buf_counter)
			{
				dir_cmp_res = strcmp(basename(dir_buffer[buf_counter]), basename(dir_buffer[buf_counter2]));
				base_cmp_res = strcmp(dirname(dir_buffer[buf_counter]), dirname(dir_buffer[buf_counter2]));
				if (base_cmp_res == 0 && dir_cmp_res == 0) return false;
			}
	return true;
}