#include <argcheck.h>

#define SH_PATH "./src/defpic.sh"
#define SHEBANG_RAW "#!/bin/sh\n"

typedef enum {
	SCRIPT_OK = 0,
	SCRIPT_BAD_NOT_EXIST,
	SCRIPT_BAD
} ScriptErrCode;

ScriptErrCode StartScript(int,char**);
	static bool DoesScriptExist();
		static bool DoesShebangExist(FILE*);
	static int ExecuteWatchLoop();

int main(int argc, char* argv[])
{
	if (AreArgsValid(argc,argv) != CHECK_OK) return 1;
	if (StartScript(argc,argv) != SCRIPT_OK) return 2;
	return 0;
}

ScriptErrCode StartScript(int arg_count,char** arg_buf)
{
	if ( false == DoesScriptExist() ) {printf("Execute script does not exist or no shebang if first line of file.Closing.\n");return SCRIPT_BAD_NOT_EXIST;}
	if ( 0 != ExecuteWatchLoop() ) {printf("Script failure. Closing.\n");return SCRIPT_BAD;}
	return SCRIPT_OK;
}

static bool DoesScriptExist()
{
	FILE *fp = fopen (SH_PATH, "r");
	if ( NULL != fp ) {

		if ( false == DoesShebangExist(fp) )
		{
			fclose(fp);
			return false;
		}

		fclose (fp);
		return true;
	}
	return false;
}

static bool DoesShebangExist(FILE* file_pointer)
{
	char check_str[sizeof(SHEBANG_RAW)];
	if ( NULL != file_pointer )
	{
		(void) fgets(check_str,sizeof(check_str),file_pointer);
		if (strcmp(check_str,SHEBANG_RAW) != 0) return false;
	}
	return true;
}

static int ExecuteWatchLoop()
{
	return system(SH_PATH);
}