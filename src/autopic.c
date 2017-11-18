#include <argcheck.h>

int main(int argc, char** argv)
{
	if (AreArgsValid(argc,argv) != 0) return 1;
	return 0;
}