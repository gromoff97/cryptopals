#include <stdio.h>
#include <string.h>

#define ARG_COUNT 2
#define HEX_SYMB_BUFFER "0123456789ABCDEFabcdef"

int main ( int argc, char const *argv[] )
{
	size_t char_counter, char_count;
	if ( ARG_COUNT != argc ) return -1;

	char_count = strlen(argv[1]);
	for ( char_counter = 0 ; char_counter < char_count; char_counter++ )
	{
		if ( NULL == strchr( HEX_SYMB_BUFFER, argv[1][char_counter] ) ) 
		{
			return -1;
		}
	}

	return 0;
}