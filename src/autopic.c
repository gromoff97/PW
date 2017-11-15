#include <stdio.h>
#include <stdlib.h>

#define REQARGC 3

int AreArgsValid(int,char**);

int main(int argc, char** argv)
{
	if (!AreArgsValid(argc,argv)) return 1;
	return 0;
}

int AreArgsValid(int argcount,char** arg_buffer)
{
	if (argcount != REQARGC)
	{
		if (argcount < REQARGC) printf("Bad. Not enough %d argument(-s) to make it work.\nClosing\n",(REQARGC-argcount));
		else printf("Bad. You should remove %d argument(-s) to make it work.\nClosing\n",(argcount-REQARGC));
		return 1;
	}
	return 0;
}