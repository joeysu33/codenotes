Compile with:

gcc -o poll.out -std=c99 poll.c

Usage:

sudo mknod -m 666 poll0.tmp p
./poll.out

On another shell:

printf a >poll0.tmp

POLLHUP

If you don't modify the source: ./poll.out outputs:

loop
POLLIN n=1 buf=a
loop
POLLHUP
loop

So:

    POLLIN happens when input becomes available
    POLLHUP happens when the file is closed by the printf
    close(pfd.fd); and pfd.fd *= -1; clean things up, and we stop receiving POLLHUP
    poll hangs forever

This is the normal operation.

You could now repoen the FIFO to wait for the next open, or exit the loop if you are done.

POLLNAL

If you comment out pfd.fd *= -1;: ./poll.out prints:

POLLIN n=1 buf=a
loop
POLLHUP
loop
POLLNVAL
loop
POLLNVAL
...

and loops forever.

So:

    POLLIN and POLLHUP and close happened as before
    since we didn't set pfd.fd to a negative number, poll keeps trying to use the fd that we closed
    this keeps returning POLLNVAL forever

So we see that this shouldn't have happened, and indicates a bug in your code.

POLLERR

I don't know how to generate a POLLERR with FIFOs. Let me know if there is way. But it should be possible with file_operations of a device driver.

Tested in Ubuntu 14.04.
