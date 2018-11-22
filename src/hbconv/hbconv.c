#include <stdio.h>
#include <stdlib.h>

#include "../../include/hbconv.h"

int main ( int argc, char const *argv[] )
{
	char* base64_buffer;

	switch( validate_arg( argc, argv[1] ) )
	{
		case READ_INVALID_COUNT : fprintf( stderr, "hbconv : Argument count is invalid.\n" ); return -1;
		case READ_INVALID_INPUT : fprintf( stderr, "hbconv : Input is invalid.\n" ); return -2;
		case READ_OK : break;
	}

	base64_buffer = convhextobase64(argv[1]);
	puts(base64_buffer);

	free(base64_buffer);
	return 0;
}