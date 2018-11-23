#ifndef _HBCONV_H_
#define _HBCONV_H_

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

cl_read_status validate_arg( int, const char* );
char* convhextobase64( const char* );

#endif