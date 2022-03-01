#include <stdio.h>   // io stuff
#include <unistd.h>  /* read, write */
#include <fcntl.h>   /* open */


int main(int argc, char *argv[]){

	if (argc < 2){
		write(2, "Did not receive output file\n", 28);  // write(stream [0 - stdin, 1 - stdount 2 - stderr], message, bytes)
		return 1;
	}

	fflush(stdout);
	
	char buffer[1025] = {0};
	ssize_t bytes = read(0, buffer, 1024);	// similar to write

	if (bytes < 0){
		write(2, "Could not read\n", 15);
		return 1;	
	} 

	int fd = open(argv[1], O_RDWR | O_CREAT, 0666); // open(file_path, mode, ??)

	if (fd < 0){
		write(2, "Open failed\n", 12);
		return 1;
	}

	write(fd, buffer, bytes);
	return 0;
}

