#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ARG_COUNT 2
#define HEX_SYMB_BUFFER "0123456789ABCDEFabcdef"
#define BLOCK_SIZE 6

int main ( int argc, char const *argv[] )
{
	size_t char_counter, char_count, block_count, block_counter;
	char block[ BLOCK_SIZE + 1 ];
	char* input_buffer;

	if ( ARG_COUNT != argc ) return -1;

	char_count = strlen(argv[1]);
	for ( char_counter = 0 ; char_counter < char_count; char_counter++ )
	{
		if ( NULL == strchr( HEX_SYMB_BUFFER, argv[1][char_counter] ) ) 
		{
			return -1;
		}
	}

	input_buffer = malloc( sizeof(char) * ( char_count  + ( char_count % 2 ) ) );
	strncpy( input_buffer + ( char_count % 2 ), argv[1], char_count );
	if ( 1 == ( char_count % 2 ) )
	{
		input_buffer[0] = '0';
		char_count++;
	}

	block_count = char_count / BLOCK_SIZE;
	if ( 0 != ( char_count % BLOCK_SIZE ) )
	{
		block_count++;
	}

	/* from first block to n-1 block */
	for ( block_counter = 0; block_counter < block_count - 1; block_counter++ )
	{
		strncpy( block, input_buffer + ( block_counter * BLOCK_SIZE ), BLOCK_SIZE );
	}

	free( input_buffer );
	return 0;
}