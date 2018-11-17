#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ARG_COUNT 2
#define HEX_SYMB_BUFFER "0123456789ABCDEFabcdef"
#define BASE64_SYMB_BUFFER "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
#define HEX_BLOCK_SIZE 6
#define SIX_BLOCK_SIZE 6
#define HEX_SIZE 4
#define BIN_BLOCK_SIZE ( HEX_BLOCK_SIZE * HEX_SIZE )

int main ( int argc, char const *argv[] )
{
	size_t char_counter, char_count, hex_block_count, hex_block_counter, hex_counter, six_counter;
	char hex_block[ HEX_BLOCK_SIZE + 1 ] = {0};
	char bin_block[ BIN_BLOCK_SIZE + 1] = {0};
	char six_block[ SIX_BLOCK_SIZE + 1 ] = {0};
	char* base64_buff = BASE64_SYMB_BUFFER;
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

	if ( hex_block_count > 1 || ( 1 == hex_block_count && 0 == ( char_count % HEX_BLOCK_SIZE ) ) )
	{
		if (hex_block_count > 1)
		{
			hex_block_count--;
		}

		/* from first block to n-1 block */
		for ( hex_block_counter = 0; hex_block_counter < hex_block_count; hex_block_counter++ )
		{
			strncpy( hex_block, input_buffer + ( hex_block_counter * HEX_BLOCK_SIZE ), HEX_BLOCK_SIZE );
			for ( hex_counter = 0; hex_counter < HEX_BLOCK_SIZE; hex_counter++ )
			{
				switch( hex_block[hex_counter] )
				{
					case '0': strncpy( bin_block + hex_counter*HEX_SIZE, "0000", HEX_SIZE+1 ); break;
					case '1': strncpy( bin_block + hex_counter*HEX_SIZE, "0001", HEX_SIZE+1 ); break;
					case '2': strncpy( bin_block + hex_counter*HEX_SIZE, "0010", HEX_SIZE+1 ); break;
					case '3': strncpy( bin_block + hex_counter*HEX_SIZE, "0011", HEX_SIZE+1 ); break;
					case '4': strncpy( bin_block + hex_counter*HEX_SIZE, "0100", HEX_SIZE+1 ); break;
					case '5': strncpy( bin_block + hex_counter*HEX_SIZE, "0101", HEX_SIZE+1 ); break;
					case '6': strncpy( bin_block + hex_counter*HEX_SIZE, "0110", HEX_SIZE+1 ); break;
					case '7': strncpy( bin_block + hex_counter*HEX_SIZE, "0111", HEX_SIZE+1 ); break;
					case '8': strncpy( bin_block + hex_counter*HEX_SIZE, "1000", HEX_SIZE+1 ); break;
					case '9': strncpy( bin_block + hex_counter*HEX_SIZE, "1001", HEX_SIZE+1 ); break;
					case 'A': strncpy( bin_block + hex_counter*HEX_SIZE, "1010", HEX_SIZE+1 ); break;
					case 'B': strncpy( bin_block + hex_counter*HEX_SIZE, "1011", HEX_SIZE+1 ); break;
					case 'C': strncpy( bin_block + hex_counter*HEX_SIZE, "1100", HEX_SIZE+1 ); break;
					case 'D': strncpy( bin_block + hex_counter*HEX_SIZE, "1101", HEX_SIZE+1 ); break;
					case 'E': strncpy( bin_block + hex_counter*HEX_SIZE, "1110", HEX_SIZE+1 ); break;
					case 'F': strncpy( bin_block + hex_counter*HEX_SIZE, "1111", HEX_SIZE+1 ); break;
					case 'a': strncpy( bin_block + hex_counter*HEX_SIZE, "1010", HEX_SIZE+1 ); break;
					case 'b': strncpy( bin_block + hex_counter*HEX_SIZE, "1011", HEX_SIZE+1 ); break;
					case 'c': strncpy( bin_block + hex_counter*HEX_SIZE, "1100", HEX_SIZE+1 ); break;
					case 'd': strncpy( bin_block + hex_counter*HEX_SIZE, "1101", HEX_SIZE+1 ); break;
					case 'e': strncpy( bin_block + hex_counter*HEX_SIZE, "1110", HEX_SIZE+1 ); break;
					case 'f': strncpy( bin_block + hex_counter*HEX_SIZE, "1111", HEX_SIZE+1 ); break;
					default : printf("something is wrong with converter. Quiting\n"); return -2;
				}
			}

			for ( six_counter = 0; six_counter < BIN_BLOCK_SIZE; six_counter = six_counter + SIX_BLOCK_SIZE )
			{
				strncpy( six_block, bin_block + six_counter, SIX_BLOCK_SIZE );
				printf("%c", base64_buff[strtoul( six_block, NULL, 2 )]);
			}
		}
	}

	memset(hex_block, 0, sizeof(char) * HEX_BLOCK_SIZE);
	memset(bin_block, 0, sizeof(char) * BIN_BLOCK_SIZE);
	strncpy( hex_block, input_buffer + hex_block_counter * HEX_BLOCK_SIZE , char_count % HEX_BLOCK_SIZE );

	if ( 0 != strlen(hex_block) )
	{
		for ( hex_counter = 0; hex_counter < ( char_count % HEX_BLOCK_SIZE ); hex_counter++ )
			{
				switch( hex_block[hex_counter] )
				{
					case '0': strncpy( bin_block + hex_counter*HEX_SIZE, "0000", HEX_SIZE+1 ); break;
					case '1': strncpy( bin_block + hex_counter*HEX_SIZE, "0001", HEX_SIZE+1 ); break;
					case '2': strncpy( bin_block + hex_counter*HEX_SIZE, "0010", HEX_SIZE+1 ); break;
					case '3': strncpy( bin_block + hex_counter*HEX_SIZE, "0011", HEX_SIZE+1 ); break;
					case '4': strncpy( bin_block + hex_counter*HEX_SIZE, "0100", HEX_SIZE+1 ); break;
					case '5': strncpy( bin_block + hex_counter*HEX_SIZE, "0101", HEX_SIZE+1 ); break;
					case '6': strncpy( bin_block + hex_counter*HEX_SIZE, "0110", HEX_SIZE+1 ); break;
					case '7': strncpy( bin_block + hex_counter*HEX_SIZE, "0111", HEX_SIZE+1 ); break;
					case '8': strncpy( bin_block + hex_counter*HEX_SIZE, "1000", HEX_SIZE+1 ); break;
					case '9': strncpy( bin_block + hex_counter*HEX_SIZE, "1001", HEX_SIZE+1 ); break;
					case 'A': strncpy( bin_block + hex_counter*HEX_SIZE, "1010", HEX_SIZE+1 ); break;
					case 'B': strncpy( bin_block + hex_counter*HEX_SIZE, "1011", HEX_SIZE+1 ); break;
					case 'C': strncpy( bin_block + hex_counter*HEX_SIZE, "1100", HEX_SIZE+1 ); break;
					case 'D': strncpy( bin_block + hex_counter*HEX_SIZE, "1101", HEX_SIZE+1 ); break;
					case 'E': strncpy( bin_block + hex_counter*HEX_SIZE, "1110", HEX_SIZE+1 ); break;
					case 'F': strncpy( bin_block + hex_counter*HEX_SIZE, "1111", HEX_SIZE+1 ); break;
					case 'a': strncpy( bin_block + hex_counter*HEX_SIZE, "1010", HEX_SIZE+1 ); break;
					case 'b': strncpy( bin_block + hex_counter*HEX_SIZE, "1011", HEX_SIZE+1 ); break;
					case 'c': strncpy( bin_block + hex_counter*HEX_SIZE, "1100", HEX_SIZE+1 ); break;
					case 'd': strncpy( bin_block + hex_counter*HEX_SIZE, "1101", HEX_SIZE+1 ); break;
					case 'e': strncpy( bin_block + hex_counter*HEX_SIZE, "1110", HEX_SIZE+1 ); break;
					case 'f': strncpy( bin_block + hex_counter*HEX_SIZE, "1111", HEX_SIZE+1 ); break;
					default : printf("something is wrong with converter. Quiting\n"); return -2;
				}
			}

			for ( six_counter = 0; six_counter < BIN_BLOCK_SIZE; six_counter = six_counter + SIX_BLOCK_SIZE )
			{
				strncpy( six_block, bin_block + six_counter, SIX_BLOCK_SIZE );
				if ( SIX_BLOCK_SIZE == strlen(six_block) )
				{
					printf("%c", base64_buff[strtoul( six_block, NULL, 2 )]);
				}

				if ( strlen(six_block) != SIX_BLOCK_SIZE && strlen(six_block) > 0 )
				{
					memset(six_block + strlen(six_block), '0', sizeof(char) * ( SIX_BLOCK_SIZE - strlen(six_block)) );
					printf("%c", base64_buff[strtoul( six_block, NULL, 2 )]);
				}

				if ( 0 == strlen(six_block) )
				{
					printf("=");
				}
			}
	}
	puts("");

	free( input_buffer );
	return 0;
}