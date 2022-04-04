/* This program will serve as the client side to an ‹AF_UNIX›
 * socket.  All it does is connect to the socket and send a simple
 * message.  The content of the message is given by the command
 * line. */

#include <unistd.h>     /* write */
#include <stdio.h>      /* perror */
#include <string.h>     /* strlen */
#include <sys/socket.h> /* socket, connect */
#include <sys/un.h>     /* sockaddr_un */

int main( int argc, const char **argv )
{
    if ( argc != 2 )
        return fputs( "need exactly 1 argument\n", stderr ), 1;

    /* Sockets are symmetric, in the sense that the first thing we
     * always do is create a socket. That socket can then become a
     * server or a client, depending on what happens next. So let's
     * create a socket: the arguments should now be familiar,
     * because they are exactly the things that we passed to
     * ‹socketpair› just a short while ago. */

    int sock_fd = socket( AF_UNIX, SOCK_STREAM, 0 );

    if ( sock_fd == -1 )
        return perror( "socket" ), 2;

    /* The socket itself is not very useful. To talk to some other
     * program, we need to ‹connect› to its listening socket, and
     * for that, we need to tell the system the «address» on which
     * the server is listening. Addresses for ‹AF_UNIX› sockets are
     * described by structures of the type ‹sockaddr_un›. */

    struct sockaddr_un sa = { .sun_family = AF_UNIX,
                              .sun_path = "./socket" };

    /* The above describes the address, now let's ask the socket to
     * connect to it. The function to do that is called ‹connect›,
     * and takes the socket file descriptor and the address, like
     * this: */

    if ( connect( sock_fd, ( struct sockaddr * ) &sa,
                  sizeof( sa ) ) == -1 )
        return perror( "connect to ./socket" ), 2;

    size_t bytes = strlen( argv[1] ) + 1;
    if ( write( sock_fd, argv[1], bytes ) != bytes )
        return perror( "write" ), 2;

    close( sock_fd );
    return 0;
}

/* Before compiling and executing this program, we will need also
 * the server part. So let's read that first and then we can try
 * both pieces:
 *
 *     $ micro server.c
 */
