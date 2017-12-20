#include <langchecker.h>
#include <string.h>

static const char eng_buf[]={".~/abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};

LangErrCode strengl( char buffer[] )
{
	for (size_t buf_counter = 0; buf_counter < strlen(buffer); buf_counter++)
			if ( NULL == strchr(eng_buf,buffer[buf_counter]) )
				return CHECK_LANG_NON_ENGL;
			
	return CHECK_LANG_OK;
}