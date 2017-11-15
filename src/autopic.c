#include <stdio.h>

#define REQARGC 3

int AreArgsValid(int);

int main(int argc, char const *argv[])
{
	if (!AreArgsValid(argc)) return 1;
	return 0;
}

int AreArgsValid(int argcount)
{
	if (argcount != REQARGC)
	{
		if (argcount < REQARGC) printf("Bad. Not enough %d argument(-s) to make it work.\nClosing\n",(REQARGC-argcount));
		else printf("Bad. You should remove %d argument(-s) to make it work.\nClosing\n",(argcount-REQARGC));
		return 1;
	}
	return 0;
}