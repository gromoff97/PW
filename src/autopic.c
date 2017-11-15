#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#define REQARGC 3

int AreArgsValid(int,char**);
	int IsDirExists(char*);
	int IsDirEmpty(char*);

int main(int argc, char** argv)
{
	if (AreArgsValid(argc,argv) != 0) return 1;
	return 0;
}

int AreArgsValid(int argcount,char** arg_buffer)
{
	size_t arg_counter = 1;
	if (argcount != REQARGC)
	{
		if (argcount < REQARGC) printf("Bad. Not enough %d argument(-s) to make it work.\nClosing\n",(REQARGC-argcount));
		else printf("Bad. You should remove %d argument(-s) to make it work.\nClosing\n",(argcount-REQARGC));
		return 1;
	}
	while (arg_counter < REQARGC)
	{
		/*printf("%s\n",arg_buffer[arg_counter]);*/
		if (IsDirExists(arg_buffer[arg_counter]) != 0) return 2;
		if (IsDirEmpty(arg_buffer[arg_counter]) != 0) return 3;
		arg_counter++;
	}
	return 0;
}

int IsDirExists(char* dir_path)
{
	DIR* dir = opendir(dir_path);
	if (dir)
	{
		closedir(dir);
		return 0;
	}
	return 1;
}

int IsDirEmpty(char* dir_path)
{
	size_t file_counter = 0;
	DIR* dir = opendir(dir_path);
    if (dir)
    {
        while (readdir(dir) != NULL)
        	file_counter++;
        closedir(dir);
    }
    if (file_counter != 2) return 1;
	return 0;
}