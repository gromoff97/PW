#include <argcheck.h>
#include <sys/inotify.h>
#include <unistd.h>

#define SH_PATH "./src/SH/defpic.sh"
#define SHEBANG_RAW "#!/bin/sh\n"
#define COMMAND_BUF_SIZE ( 256 )
#define STOP_FILE_NAME ".end_inotify_properly"
#define EVENT_SIZE ( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN ( 1024 * ( EVENT_SIZE + 16 ) )

typedef enum {
	SCRIPT_OK = 0,
	SCRIPT_BAD_NOT_EXIST,
	SCRIPT_BAD
} ScriptErrCode;

ScriptErrCode StartScript(int,char**);
	static bool DoesScriptExist();
		static bool DoesShebangExist(FILE*);
	static int ExecuteWatchLoop(char*[]);
		static bool IsPic(char[]);
		static int DelFile(char*,char*);
		static bool IsStopFile(char*);

int main(int argc, char* argv[])
{
	if (AreArgsValid(argc,argv) != CHECK_OK) return 1;
	if (StartScript(argc,argv) != SCRIPT_OK) return 2;
	return 0;
}

ScriptErrCode StartScript(int arg_count,char** arg_buf)
{
	if ( false == DoesScriptExist() ) {printf("Execute script does not exist or no shebang if first line of file.Closing.\n");return SCRIPT_BAD_NOT_EXIST;}
	if ( 0 != ExecuteWatchLoop(arg_buf) ) {printf("Script failure. Closing.\n");return SCRIPT_BAD;}
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

static int ExecuteWatchLoop(char *argv[])
{
	int length,i,fd,wd;
	char event_buffer[EVENT_BUF_LEN], *watch_folder = argv[1],**out_folder_buf = &argv[2]; // first folder is watch folder. Others are out-folders.

	fd = inotify_init();
	if ( fd < 0 ) return 1;

	wd = inotify_add_watch( fd, watch_folder, IN_CLOSE_WRITE | IN_CREATE | IN_MOVED_TO);

	while (true)
	{
		i = 0;
		length = read( fd, event_buffer, EVENT_BUF_LEN ); 
		if ( length < 0 ) return 2;
		while ( i < length )
		{
			struct inotify_event *event = ( struct inotify_event * ) &event_buffer[ i ];
			//here will be conditions
			i += EVENT_SIZE + event->len;
		}
	}

	inotify_rm_watch( fd, wd );
	close( fd );
	return 0;
}

static bool IsPic(char file_name[])
{
	char ext[5];
	memcpy( ext, &file_name[strlen(file_name)-4], 4 );
	ext[4] = '\0';
	if (0 == strcmp(".jpg\0",ext) || 0 == strcmp(".png\0",ext)) return true;
	return false;
}

static int DelFile(char* file_name,char* dir_name)
{
	char command_buffer[COMMAND_BUF_SIZE];
	memset(command_buffer,0,COMMAND_BUF_SIZE);
	(void) strcat(command_buffer,"cd ");
	(void) strcat(command_buffer,dir_name);
	(void) strcat(command_buffer," && rm -rf ");
	(void) strcat(command_buffer,file_name);
	(void) strcat(command_buffer," && (cd -) > /dev/null");
	return system(command_buffer);
}

static bool IsStopFile(char* file_name)
{
	if ( 0 != strcmp(file_name,STOP_FILE_NAME) ) return false;
	return true;
}