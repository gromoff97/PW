#include <argchecker.h>
#include <langchecker.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <libgen.h>
#include <string.h>
#include <stdint.h>

static bool IsArgCountValid( int32_t );
static bool IsDirExists( char* );
static bool IsDirEmpty( char* );
static bool AreDirNamesUnique( char*[] );

CheckArgErrCode AreArgsValid( int arg_count, char* arg_buffer[] )
{
	if ( false == IsArgCountValid( arg_count ) ) { printf( "bad arguments count.Closing\n" ); return CHECK_INVALID_ARG_COUNT; }

	for ( size_t arg_counter = 1; arg_counter < REQARGC; arg_counter++ )
	{
		if ( CHECK_LANG_OK != strengl( arg_buffer[arg_counter] ) ) { printf("non-english string was found in following command-line argument: %s\n", arg_buffer[arg_counter] ); return CHECK_NON_ENGL; }
		if ( false == IsDirExists( arg_buffer[ arg_counter ] ) ) { printf( "Directory \'%s\' does not exist. Closing\n", arg_buffer[arg_counter] ); return CHECK_DIR_NOT_EXISTS; }
	}

	if ( false == IsDirEmpty( arg_buffer[ 1 ] ) ) { printf( "Watch-Directory \'%s\' is not empty. Closing\n", arg_buffer[ 1 ] ); return CHECK_DIR_NOT_EMPTY; }

	if ( false == AreDirNamesUnique( arg_buffer ) ){ printf( "Directories names are not unique. Closing\n" ); return CHECK_DIRS_NAMES_NOT_UNIQUE; }

	return CHECK_OK;
}

static bool IsArgCountValid( int32_t arg_count )
{
	if ( REQARGC != arg_count ) return false;
	return true;
}

static bool IsDirExists( char* dir_path )
{
	DIR* dir = opendir( dir_path );
	if ( dir )
	{
		closedir( dir );
		return true;
	}
	return false;
}

static bool IsDirEmpty( char* dir_path )
{
	size_t file_counter = 0;
	DIR* dir = opendir( dir_path );
    if ( dir )
    {
        while ( NULL != readdir( dir ) )
        	file_counter++; /*increment if we find a file*/
        closedir( dir );
    }
    if ( 2 != file_counter ) return false; /*in linux in each directory exist at least 2 files called "." and ".."*/
	return true;
}

static bool AreDirNamesUnique( char* dir_buffer[] )
/*dirname-foo changes his parametr to it's return literal. We use dirname multiple times so we got to save previous dir_buffer's value using strcpy-foo*/
{
	int8_t dir_cmp_res,base_cmp_res;
	char tmp1[ MAX_PATH_BUF_SIZE ], tmp2[ MAX_PATH_BUF_SIZE ];

	for ( size_t buf_counter1 = 1; buf_counter1 < REQARGC; buf_counter1++ )
	{
		memset( tmp1, 0, MAX_PATH_BUF_SIZE );
		(void) strcpy( tmp1, dir_buffer[ buf_counter1 ] );

		for ( size_t buf_counter2 = buf_counter1 + 1; buf_counter2 < REQARGC; buf_counter2++ )
		{
			memset( tmp2, 0, MAX_PATH_BUF_SIZE );
			(void) strcpy( tmp2, dir_buffer[ buf_counter2 ] );

			base_cmp_res = strcmp( basename( dir_buffer[ buf_counter1 ] ), basename( dir_buffer[ buf_counter2 ] ) );
			dir_cmp_res = strcmp( dirname(dir_buffer[ buf_counter1 ] ), dirname( dir_buffer[ buf_counter2 ] ) );

			(void) strcpy( dir_buffer[ buf_counter1 ], tmp1);
			(void) strcpy( dir_buffer[ buf_counter2 ], tmp2);
				
			if ( 0 == base_cmp_res && 0 == dir_cmp_res ) return false;
		}
	}
	return true;
}