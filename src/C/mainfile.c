#include <watcher.h>

int main( int argc, char* argv[] )
{
	if ( StartWatching(argc,argv) != SCRIPT_OK ) return 1;
	return 0;
}

