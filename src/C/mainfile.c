#include <watcher.h>

int main(int argc, char* argv[])
{
	if (StartScript(argc,argv) != SCRIPT_OK) return 2;
	return 0;
}

