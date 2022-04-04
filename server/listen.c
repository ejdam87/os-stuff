#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(void)
{

	
    int sock_fd = socket( AF_UNIX, SOCK_STREAM, 0 );
    
    if ( sock_fd == -1 ){
    	return 1;
    }

    struct sockaddr_un sa = { .sun_family = AF_UNIX,
                              .sun_path = "./socket" };

    unlink("./socket");

    if (bind(sock_fd,(struct sockaddr*) &sa, sizeof(sa))){
    	return 1;
    }
        
    if (listen(sock_fd, 5 ) != 0){
    	return 1;
    }

    int client_fd;
    char path[200];
    
    while ((client_fd = accept(sock_fd, NULL, NULL )) >= 0)
    {
        if (read(client_fd, path, 200) < 0)
           return 1;

		pid_t pid = fork();
	
		if (pid < 0) {
			return 1;
		}
		
		if (pid == 0) {
		
		    close(sock_fd);
	        if (execl(path, path, NULL) == -1)
	             return 1;
	
	        return 13;
	        
	        }
	
		if (pid > 0) {
		    int status;
		    if (waitpid(pid, &status, 0) == -1) {
		    	return 1;
		    }
		}
		
	        close( client_fd );	
	    
	}
}
