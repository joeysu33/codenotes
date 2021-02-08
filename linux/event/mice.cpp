#include <sys/types.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/input.h>

void listen_mice(const char *dev, int timeout)
{
    char buf[256];
    int n_len;

    int retval;
    fd_set readfds;
    struct timeval tv;

    int fd = open(dev, O_RDONLY);

    if (fd < 0)
    {
        perror(dev);
        return;
    }

    while (1)
    {
        FD_ZERO(&readfds);
        FD_SET(fd, &readfds);
        tv.tv_sec = timeout;
        tv.tv_usec = 0;
        if((retval = select(fd+1, &readfds, NULL, NULL, &tv)) == 1)
        {
            if ((n_len = read(fd, buf, sizeof(buf))) > 0)
            {
                if (n_len == 3)
                {
                    printf("Button: %d, xRef=%d, yRef=%d\n", buf[0]&0x07, buf[1], buf[2]);
                }
            }
        }
        else
        {
            break;
        }
    }

    close(fd);
}

void listen_mouse(int timeout)
{
    listen_mice("/dev/input/mice", timeout);
}

int main(int argc, char **argv)
{
    listen_mouse (20);
    printf("mouse timeout\n");
    return 0;
}



