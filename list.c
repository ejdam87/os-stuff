#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>


int main(void){

	DIR *cwd = opendir(".");
	struct stat st;

	if (!cwd){
		fprintf(stderr, "Failed to open cwd");
		exit(1);
	}

	struct dirent *dirp;
	char* file_name;
	char type;

	char target[PATH_MAX];
	ssize_t bytes;
	
	while (1){

		dirp = readdir(cwd);

		if (!dirp){
			break;
		}

		file_name = dirp -> d_name;

		// Determine type
		
		if (dirp -> d_type == DT_DIR){
			type = 'd';
		}
		else if (dirp -> d_type == DT_LNK){
			type = 'l';
		}
		else if ( dirp -> d_type == DT_REG){
			type = 'f';
		}
		else{
			type = 'u'; // unexpected
		}
		

		if (lstat(file_name, &st) == -1){
			fprintf(stderr, "Failed lstat\n");
			return 1;
		}

		if (type == 'l'){
			bytes = readlink(file_name, target, sizeof(target) - 1);
		}

		if (bytes == -1){
			fprintf(stderr, "Readlink failed\n");
			return 1;
		}

		if (type == 'l'){
			printf("%c %lu %s %lu %lu ... %s\n", type, st.st_ino, file_name, st.st_nlink, st.st_size, target);
		}
		
		else{
			printf("%c %lu %s %lu %lu\n", type, st.st_ino, file_name, st.st_nlink, st.st_size);
		}
		
	}

	closedir(cwd);
	
}
