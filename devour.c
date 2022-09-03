/*
 * devour
 * X11 window swallower
 */

#include <X11/Xlib.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    (void)argc;

    int rev;
    Window win;

    Display* dis = XOpenDisplay(0);

    XGetInputFocus(dis, &win, &rev);
    XUnmapWindow(dis, win);
    XFlush(dis);

    int pid = fork();
    if (pid == 0) {
        execvp(argv[1], argv + 1);
    } else {
        wait(NULL);
    }

    XMapWindow(dis, win);
    XCloseDisplay(dis);

    return 0;
}
