CC=gcc

hbconv: src/hbconv.c
	$(CC) -o build/hbconv src/hbconv.c