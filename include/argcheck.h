#define REQARGC 3

typedef enum {
	CHECK_OK = 0,
	CHECK_INVALID_ARG_COUNT,
	CHECK_DIR_NOT_EXISTS,
	CHECK_DIR_NOT_EMPTY,
	CHECK_DIRS_NAMES_NOT_UNIQUE
} CheckArgErrCode;

CheckArgErrCode AreArgsValid(int,char**);
	static bool IsArgCountValid(int);
	static bool IsDirExists(char*);
	static bool IsDirEmpty(char*);
	static bool AreDirNamesUnique(char**);