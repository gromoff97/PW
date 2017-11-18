#include <argcheck.h>

int main(int argc, char** argv)
{
	if (AreArgsValid(argc,argv) != CHECK_OK) return 1;
	return 0;
}