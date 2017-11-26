#include <watcher.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static bool DoesScriptExist();
	static bool DoesShebangExist(FILE*);
static int ExecuteWatchLoop(int,char*[]);
	static bool IsPic(char[]);
	static int DelFile(char*,char*);
	static bool IsStopFile(char*);
	static int ExecuteShScript(int,char*[],char *);


ScriptErrCode StartScript(int arg_count,char** arg_buf)
{
	if ( false == DoesScriptExist() ) {printf("Execute script does not exist or no shebang in first line of file.Closing.\n");return SCRIPT_BAD_NOT_EXIST;}
	if ( 0 != ExecuteWatchLoop(arg_count,arg_buf) ) {printf("Script failure. Closing.\n");return SCRIPT_BAD;}
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

static int ExecuteWatchLoop(int argc,char *argv[])
{
	int length,i,fd,wd;
	char event_buffer[EVENT_BUF_LEN], *watch_folder = argv[1]; // first folder is watch folder. Others are out-folders.

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
			if ( event->len )
			{
				if ( event-> mask & IN_CREATE )
				{
					if ( event->mask & IN_ISDIR )
						{if ( 0 != DelFile(event->name,watch_folder) ) return 3;}
					else 
						if ( IsStopFile(event->name) == true) return 0;
				}

				if ( (event->mask & IN_CLOSE_WRITE) || (event->mask & IN_MOVED_TO) )
				{
					if ( (!(event->mask & IN_ISDIR) && false == IsPic(event->name)) || (event->mask & IN_ISDIR))
						{if ( 0 != DelFile(event->name,watch_folder) ) return 3;}
					else
						if (ExecuteShScript(argc-1,&argv[1],event->name) != 0) return 4;
				}
 				
			}
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
	sprintf(command_buffer,"./src/SH/delfile.sh %s %s",dir_name,file_name);
	return system(command_buffer);
}

static bool IsStopFile(char* file_name)
{
	if ( 0 != strcmp(file_name,STOP_FILE_NAME) ) return false;
	return true;
}

static int ExecuteShScript(int dir_count,char* dir_buf[],char *pic_name)
{
	char command_buffer[COMMAND_BUF_SIZE];
	memset(command_buffer,0,COMMAND_BUF_SIZE);
	(void) strcat(command_buffer,SH_PATH);
	(void) strcat(command_buffer," ");
	(void) strcat(command_buffer,pic_name);
	(void) strcat(command_buffer," ");
	for (int counter = 0; counter < dir_count; counter++)
	{
		(void) strcat(command_buffer,dir_buf[counter]);
		(void) strcat(command_buffer," ");
	}
	if ( 0 != system(command_buffer) ) return 1;
	return 0;
}