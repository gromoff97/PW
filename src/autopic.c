#include <argcheck.h>

#define SH_PATH "src/defpic.sh"

typedef enum {
	SCRIPT_OK = 0,
	SCRIPT_BAD_NOT_EXIST,
	SCRIPT_BAD
} ScriptErrCode;

ScriptErrCode StartScript(char**);
	static bool DoesScriptExist();
	static int ExecuteMainScript();

int main(int argc, char* argv[])
{
	if (AreArgsValid(argc,argv) != CHECK_OK) return 1;
	if (StartScript(argv) != SCRIPT_OK) return 2;
	return 0;
}

ScriptErrCode StartScript(char** arg_buf)
{
	if ( false == DoesScriptExist() ) {printf("Execute script does not exist.Closing.\n");return SCRIPT_BAD_NOT_EXIST;}
	if ( 0 != ExecuteMainScript() ) {printf("Script failure. Closing.\n");return SCRIPT_BAD;}
	return SCRIPT_OK;
}

static bool DoesScriptExist()
{
	FILE *fp = fopen (SH_PATH, "r");
	if (fp!=NULL) {fclose (fp);return true;}
	return false;
}

static int ExecuteMainScript()
{
	return 0;
}