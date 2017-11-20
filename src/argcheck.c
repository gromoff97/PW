#include <argcheck.h>

static bool IsArgCountValid(int);
static bool IsDirExists(char*);
static bool IsDirEmpty(char*);
static bool AreDirNamesUnique(char*[]);

CheckArgErrCode AreArgsValid(int arg_count,char* arg_buffer[])
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
        	file_counter++; /*increment if we find a file*/
        closedir(dir);
    }
    if (file_counter != 2) return false; /*in linux in each directory exist at least 2 files called "." and ".."*/
	return true;
}

static bool AreDirNamesUnique(char* dir_buffer[])
/*dirname-foo changes his parametr to it's return literal. We use dirname multiple times so we got to save previous dir_buffer's value using strcpy-foo*/
{
	int dir_cmp_res,base_cmp_res;
	char *tmp1,*tmp2;
	for (size_t buf_counter1 = 1; buf_counter1 < REQARGC; buf_counter1++)
		for (size_t buf_counter2 = 1; buf_counter2 < REQARGC; buf_counter2++)
			if (buf_counter2 != buf_counter1)
			{
				tmp1 = (char *) malloc(sizeof(char)*sizeof(dir_buffer[buf_counter1]));
				tmp2 = (char *) malloc(sizeof(char)*sizeof(dir_buffer[buf_counter2]));
				(void) strcpy(tmp1,dir_buffer[buf_counter1]);
				(void) strcpy(tmp2,dir_buffer[buf_counter2]);
				base_cmp_res = strcmp(basename(dir_buffer[buf_counter1]), basename(dir_buffer[buf_counter2]));
				dir_cmp_res = strcmp(dirname(dir_buffer[buf_counter1]), dirname(dir_buffer[buf_counter2]));
				(void) strcpy(dir_buffer[buf_counter1],tmp1);
				(void) strcpy(dir_buffer[buf_counter2],tmp2);
				free(tmp2);
				free(tmp1);
				if (base_cmp_res == 0 && dir_cmp_res == 0) return false;
			}
	return true;
}