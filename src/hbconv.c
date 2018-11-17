#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ARG_COUNT 2
#define HEX_SYMB_BUFFER "0123456789ABCDEFabcdef"
#define HEX_BLOCK_SIZE 6
#define BIN_BLOCK_SIZE ( HEX_BLOCK_SIZE * 4 )

int main ( int argc, char const *argv[] )
{
	size_t char_counter, char_count, hex_block_count, hex_block_counter;
	char hex_block[ HEX_BLOCK_SIZE + 1 ] = {0};
	char bin_block[ BIN_BLOCK_SIZE + 1] = {0};
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

	hex_block_count = char_count / HEX_BLOCK_SIZE;
	if ( 0 != ( char_count % HEX_BLOCK_SIZE ) )
	{
		hex_block_count++;
	}

	/* from first block to n-1 block */
	for ( hex_block_counter = 0; hex_block_counter < hex_block_count - 1; hex_block_counter++ )
	{
		strncpy( hex_block, input_buffer + ( hex_block_counter * HEX_BLOCK_SIZE ), HEX_BLOCK_SIZE );
	}

	free( input_buffer );
	return 0;
}