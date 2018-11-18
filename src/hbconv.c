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

typedef enum cl_read_status {
	READ_OK = 0,
	READ_INVALID_COUNT,
	READ_INVALID_INPUT
} cl_read_status;

static int is_str_hex( const char* );
cl_read_status validate_arg( int, const char* );

static char* get_bin_from_hex( char );

int main ( int argc, char const *argv[] )
{
	size_t char_count, hex_block_count, hex_block_counter, hex_counter, six_counter;
	char hex_block[ HEX_BLOCK_SIZE + 1 ] = {0};
	char bin_block[ BIN_BLOCK_SIZE + 1] = {0};
	char six_block[ SIX_BLOCK_SIZE + 1 ] = {0};
	char* base64_buff = BASE64_SYMB_BUFFER;
	char* input_buffer;

	switch( validate_arg( argc, argv[1] ) )
	{
		case READ_INVALID_COUNT : fprintf( stderr, "hbconv : Argument count is invalid.\n" ); return -1;
		case READ_INVALID_INPUT : fprintf( stderr, "hbconv : Input is invalid.\n" ); return -2;
		case READ_OK : break;
	}

	char_count = strlen(argv[1]);
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
		if ( hex_block_count > 1 && 0 != ( char_count % HEX_BLOCK_SIZE ) )
		{
			hex_block_count--;
		}

		/* from first block to n-1 block */
		for ( hex_block_counter = 0; hex_block_counter < hex_block_count; hex_block_counter++ )
		{
			strncpy( hex_block, input_buffer + ( hex_block_counter * HEX_BLOCK_SIZE ), HEX_BLOCK_SIZE );
			for ( hex_counter = 0; hex_counter < HEX_BLOCK_SIZE; hex_counter++ )
			{
				strcpy( bin_block + hex_counter*HEX_SIZE, get_bin_from_hex(hex_block[hex_counter]) );
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


static int is_str_hex( const char* buffer )
{
	size_t char_count, char_counter; 
	if ( NULL == buffer ) return -1;

	char_count = strlen( buffer );
	for ( char_counter = 0 ; char_counter < char_count; char_counter++ )
		if ( NULL == strchr( HEX_SYMB_BUFFER, buffer[char_counter] ) )
			return -2;

	return 0;
}

cl_read_status validate_arg( int argument_count, const char* input_buffer )
{
	if ( ARG_COUNT != argument_count ) return READ_INVALID_COUNT;
	if ( NULL == input_buffer || 0 != is_str_hex( input_buffer ) )
		return READ_INVALID_INPUT;
	return READ_OK;
}

static char* get_bin_from_hex( char hex_symbol )
{
	static char bin_code[5];

	if ( NULL == strchr( HEX_SYMB_BUFFER, hex_symbol ) )
		return NULL;

	switch( hex_symbol )
	{
		case '0': strcpy( bin_code,"0000" ); break;
		case '1': strcpy( bin_code,"0001" ); break;
		case '2': strcpy( bin_code,"0010" ); break;
		case '3': strcpy( bin_code,"0011" ); break;
		case '4': strcpy( bin_code,"0100" ); break;
		case '5': strcpy( bin_code,"0101" ); break;
		case '6': strcpy( bin_code,"0110" ); break;
		case '7': strcpy( bin_code,"0111" ); break;
		case '8': strcpy( bin_code,"1000" ); break;
		case '9': strcpy( bin_code,"1001" ); break;

		case 'A': strcpy( bin_code,"1010" ); break;
		case 'B': strcpy( bin_code,"1011" ); break;
		case 'C': strcpy( bin_code,"1100" ); break;
		case 'D': strcpy( bin_code,"1101" ); break;
		case 'E': strcpy( bin_code,"1110" ); break;
		case 'F': strcpy( bin_code,"1111" ); break;

		case 'a': strcpy( bin_code,"1010" ); break;
		case 'b': strcpy( bin_code,"1011" ); break;
		case 'c': strcpy( bin_code,"1100" ); break;
		case 'd': strcpy( bin_code,"1101" ); break;
		case 'e': strcpy( bin_code,"1110" ); break;
		case 'f': strcpy( bin_code,"1111" ); break;

		default :
			fprintf( stderr, "hbconv : Error(UB) during converting from hex-code to binary code.\n" );
			return NULL;
	}

	return bin_code;
}