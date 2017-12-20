#ifndef _LANGCHECKER_H_
#define _LANGCHECKER_H_
#define ACCEPT_SYMB_COUNT ( 55 ) /*eng. lower and upper-cases + "~" "." "/"*/

typedef enum {
	CHECK_LANG_OK = 0,
	CHECK_LANG_BAD
} LangErrCode;

LangErrCode strengl( char * );

#endif