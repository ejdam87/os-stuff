/* The C functions that correspond to ‹ln› are ‹link› and ‹symlink›.
 * There is also ‹readlink›. They are all system calls and their
 * manuals live in section 2. Let's ‹#include› things we'll need: */

#include <unistd.h>   /* link, symlink, readlink */
#include <sys/stat.h> /* mkdir */
#include <fcntl.h>    /* open */
#include <stdio.h>    /* perror */
#include <stdlib.h>   /* exit */

int main()
{
    if ( open( "file", O_CREAT, 0666 ) < 0 ) /* make a test file */
        perror( "creating 'file'" ), exit( 1 );
    if ( mkdir( "dir", 0666 ) != 0 )         /* and a directory */
        perror( "creating 'dir'" ), exit( 1 );

    /* As usual, we check the exit codes in man pages. For ‹link›
     * and ‹symlink›, they are the usual 0 = success. But ‹readlink›
     * behaves like ‹read›, returning the number of bytes, so we
     * have to watch out there. */

    if ( link( "file", "link" ) != 0 )
        perror( "creating link" ), exit( 1 );

    if ( link( "dir", "dirlink" ) != 0 )
        perror( "creating dirlink" ); /* we expect this to fail */

    /* Now let's look at symlinks. */

    if ( symlink( "file", "symlink" ) != 0 )
        perror( "creating symlink" ), exit( 1 );

    if ( symlink( "dir", "dirlink" ) != 0 )
        perror( "creating (symbolic) dirlink" ), exit( 1 );

    char buffer[ 60 ] = { 0 };
    if ( readlink( "dirlink", buffer, 59 ) < 0 )
        perror( "readlink dirlink" ), exit( 1 );

    printf( "readlink on dirlink gave %s\n", buffer );
    if ( readlink( "dir", buffer, 59 ) < 0 )
        perror( "readlink dir" );
}

/* We do not clean up so that you can check the resulting files and
 * links with ‹stat› or ‹ls -l›. However, you will have to clean up
 * by hand. I am sure you know how (you can use ‹rm
 * -d›). That was links in C. Please go on to ‹3.txt›. */
