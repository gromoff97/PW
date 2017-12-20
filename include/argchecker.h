#ifndef _ARGCHECKER_H_
#define _ARGCHECKER_H_

#define REQARGC ( 3 )
#define MAX_PATH_BUF_SIZE ( 256 )

typedef enum {
	CHECK_OK = 0,
	CHECK_INVALID_ARG_COUNT,
	CHECK_NON_ENGL,
	CHECK_DIR_NOT_EXISTS,
	CHECK_DIR_NOT_EMPTY,
	CHECK_DIRS_NAMES_NOT_UNIQUE
} CheckArgErrCode;

CheckArgErrCode AreArgsValid( int, char** );

#endif