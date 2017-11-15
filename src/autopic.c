#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#define REQARGC 3

int AreArgsValid(int,char**);
	int IsDirExists(char*);

int main(int argc, char** argv)
{
	if (!AreArgsValid(argc,argv)) return 1;
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
		arg_counter++;
	}
	return 0;
}

int IsDirExists(char* dir_path)
{
	return 0;
}