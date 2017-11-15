#include <stdio.h>

#define REQARGC 3

int CheckArgs(int);

int main(int argc, char const *argv[])
{
	if (!CheckArgs(argc)) return 1;
	return 0;
}

int CheckArgs(int argcount)
{
	if (argcount != REQARGC)
	{
		if (argcount < REQARGC)
			printf("Bad. Not enough %d argument(-s) to make it work.\n",(REQARGC-argcount));
		else
			printf("Bad. You should remove %d argument(-s) to make it work.\n",(argcount-REQARGC));
		return 1;
	}
	return 0;
}