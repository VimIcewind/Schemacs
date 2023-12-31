#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

static struct termios raw;
static struct winsize size;

int raw_on(void)
{

    if (tcgetattr(STDIN_FILENO, &raw) == -1)
        return -1;


    raw.c_lflag &= ~ECHO;
    raw.c_lflag &= ~ECHONL;
    raw.c_lflag &= ~ICANON;
    raw.c_lflag &= ~ISIG;
    raw.c_lflag &= ~IEXTEN;


    // raw.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    // raw.c_oflag &= ~(OPOST);
    // raw.c_cflag |= (CS8);
    // raw.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    // raw.c_cc[VMIN] = 1;
    // raw.c_cc[VTIME] = 0;

    return tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


int raw_off(void)
{

    if (tcgetattr(STDIN_FILENO, &raw) == -1)
        return -1;


    raw.c_lflag |= ECHO;
    raw.c_lflag |= ICANON;
    raw.c_lflag |= ISIG;

    return tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}



int get_row(void)
{
    ioctl(STDIN_FILENO, TIOCGWINSZ, &size);
    return size.ws_row;
}

int get_col(void)
{
    ioctl(STDIN_FILENO, TIOCGWINSZ, &size);
    return size.ws_col;
}
