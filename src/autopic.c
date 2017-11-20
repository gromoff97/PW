#include <argcheck.h>

typedef enum {
	SCRIPT_OK = 0,
	SCRIPT_BAD
} ScriptErrCode;

ScriptErrCode ExecuteScript(char**);
	static bool DoesScriptExist();

int main(int argc, char** argv)
{
	if (AreArgsValid(argc,argv) != CHECK_OK) return 1;
	if (ExecuteScript(argv) != SCRIPT_OK) return 2;
	return 0;
}

ScriptErrCode ExecuteScript(char** arg_buf)
{
	return SCRIPT_OK;
}

static bool DoesScriptExist()
{
	return true;
}