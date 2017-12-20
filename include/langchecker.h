#ifndef _LANGCHECKER_H_
#define _LANGCHECKER_H_

typedef enum {
	CHECK_LANG_OK = 0,
	CHECK_LANG_NON_ENGL
} LangErrCode;

LangErrCode strengl( char * );

#endif