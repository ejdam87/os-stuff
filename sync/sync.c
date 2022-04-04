#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int exists(char* filename){
	struct stat buffer;

	int exist = stat(filename, &buffer);
	return exist;
}


int main(){

	pid_t pid = fork();

	if (pid < 0){
		return 2;
	}

	if (pid == 0){
		// child

		if (execl("./sync.sh", "./sync.sh", NULL) == -1){
			return 2;
		}

		return 13;
	}
	
	if (pid > 0){

		while (exists("file1.txt") != 0){
			sleep(1);
		}
	
		int fd1 = open("file1.txt", O_RDONLY);
		if (fd1 < 0){
			return 1;
		}

		char buffer[2000] = {0};
		ssize_t have_read = read(fd1, buffer, 2000);
		if (have_read < 0){
			return 1;
		}

		close(fd1);
		
		int fd2 = open("file2.txt", O_CREAT | O_RDWR, 0666);

		if (fd2 < 0){
			return 1;
		}

		if (write(fd2, buffer, have_read) < 0){
			return 1;
		}

	    close(fd2);

	    int status;

	    if ( waitpid(pid, &status, 0) == -1 ){
	    	return 2;
	    }

		if (WIFEXITED(status)){
			printf("%d\n", WEXITSTATUS(status));
		}

		return 0;
			
	}
	
}
