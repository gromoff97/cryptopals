#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ARG_COUNT 2
#define HEX_SYMB_BUFFER "0123456789ABCDEFabcdef"
#define BIN_SYMB_BUFFER "01"
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
static int is_str_bin( const char* );
static char get_bchr_from_sextet( const char* );

int main ( int argc, char const *argv[] )
{
	size_t char_count, hex_block_count, hex_block_counter, hex_counter, hex_count, six_counter, chars_left_count, odd_flag;
	char hex_block[ HEX_BLOCK_SIZE + 1 ] = {0};
	char bin_block[ BIN_BLOCK_SIZE + 1] = {0};
	char six_block[ SIX_BLOCK_SIZE + 1 ] = {0};
	char* input_buffer;

	switch( validate_arg( argc, argv[1] ) )
	{
		case READ_INVALID_COUNT : fprintf( stderr, "hbconv : Argument count is invalid.\n" ); return -1;
		case READ_INVALID_INPUT : fprintf( stderr, "hbconv : Input is invalid.\n" ); return -2;
		case READ_OK : break;
	}

	char_count = strlen(argv[1]);
	odd_flag = char_count % 2;
	input_buffer = malloc( sizeof(char) * ( char_count  + odd_flag ) );
	strncpy( input_buffer + odd_flag, argv[1], char_count );
	if ( 1 == odd_flag )
	{
		input_buffer[0] = '0';
		char_count++;
	}

	hex_block_count = char_count / HEX_BLOCK_SIZE;
	chars_left_count = char_count % HEX_BLOCK_SIZE;
	if ( 0 != chars_left_count )
	{
		hex_block_count++;
	}

	for ( hex_block_counter = 0; hex_block_counter < hex_block_count; hex_block_counter++ )
	{
		strncpy( hex_block, input_buffer + ( hex_block_counter * HEX_BLOCK_SIZE ), HEX_BLOCK_SIZE );

		if ( hex_block_counter == ( hex_block_count - 1 ) && chars_left_count != 0 )
		{
			hex_count = chars_left_count;
			memset(bin_block, 0, sizeof(char) * BIN_BLOCK_SIZE);
		}
		else
			hex_count = HEX_BLOCK_SIZE;

		for ( hex_counter = 0; hex_counter < hex_count; hex_counter++ )
		{
			strcpy( bin_block + hex_counter*HEX_SIZE, get_bin_from_hex(hex_block[hex_counter]) );
		}

		for ( six_counter = 0; six_counter < BIN_BLOCK_SIZE; six_counter = six_counter + SIX_BLOCK_SIZE )
		{
			strncpy( six_block, bin_block + six_counter, SIX_BLOCK_SIZE );
			printf("%c", get_bchr_from_sextet(six_block));
		}
	}
	puts("");

	free( input_buffer );
	return 0;
}


static int is_str_hex( const char* buffer )
{
	if ( NULL == buffer ) return -1;
	if ( 0 == buffer[ strspn( buffer, HEX_SYMB_BUFFER ) ] ) return 0;
	return -2;
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

static int is_str_bin( const char* buffer )
{
	if ( NULL == buffer ) return -1;
	if ( 0 == buffer[ strspn( buffer, BIN_SYMB_BUFFER ) ] ) return 0;
	return -2;
}

static char get_bchr_from_sextet( const char* sextet_buffer )
{
	static const char* base64_buffer = BASE64_SYMB_BUFFER;
	static char tmp_buffer[SIX_BLOCK_SIZE + 1] = {0};
	size_t sextet_buffer_len;

	if ( NULL == sextet_buffer ) return '*';

	sextet_buffer_len = strlen( sextet_buffer );
	if ( sextet_buffer_len > 6 ) return '*';

	if ( 0 == sextet_buffer_len ) return '=';

	strcpy( tmp_buffer, sextet_buffer );
	if ( SIX_BLOCK_SIZE != sextet_buffer_len )
		memset( tmp_buffer + sextet_buffer_len, '0', sizeof(char) * ( SIX_BLOCK_SIZE - sextet_buffer_len ) );

	return base64_buffer[strtoul( tmp_buffer, NULL, 2 )];
}