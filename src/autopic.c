#include <argcheck.h>

typedef enum {
	SCRIPT_OK = 0,
	SCRIPT_BAD
} ScriptErrCode;

int main(int argc, char** argv)
{
	if (AreArgsValid(argc,argv) != CHECK_OK) return 1;
	return 0;
}