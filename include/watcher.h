#ifndef _WATCHER_H_
#define _WATCHER_H_

#define SH_MAIN_PATH "./src/SH/defpic.sh"
#define SH_DELFILE_PATH "./src/SH/delfile.sh"
#define SHEBANG_RAW "#!/bin/bash\n"
#define COMMAND_BUF_SIZE ( 256 )
#define STOP_FILE_NAME ".end_inotify_properly"
#define EVENT_SIZE ( sizeof ( struct inotify_event ) )
#define EVENT_BUF_LEN ( 1024 * ( EVENT_SIZE + 16 ) )
#define SH_FILE_COUNT ( 2 )

typedef enum {
	SCRIPT_OK = 0,
	SCRIPT_BAD_START_ARGS,
	SCRIPT_BAD_NOT_EXIST,
	SCRIPT_BAD
} ScriptErrCode;

ScriptErrCode StartWatching( int, char** );

#endif