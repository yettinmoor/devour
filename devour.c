/*
 * devour
 * window Manager agnostic swallowing feature for terminal emulators
 */

#include <X11/Xlib.h>
#include <stdlib.h>
#include <string.h>

void run_command(char** argv) {
   int is_safe = 1;
   char cmd[512] = {0};

   while (*++argv) {
      if (!strcmp(*argv, "--")) {
         is_safe = 0;
         continue;
      }
      if (is_safe) {
         strcat(cmd, *argv);
      } else {
         while (**argv) {
            if (**argv == ' ') strcat(cmd, "\\");
            strncat(cmd, &*(*argv)++, 1);
         }
      }
      strcat(cmd, " ");
   }
   system(cmd);
}

int main(int argc, char** argv) {
   int rev;
   Window win;
   Display* dis = XOpenDisplay(0);

   XGetInputFocus(dis, &win, &rev);
   XUnmapWindow(dis, win);
   XFlush(dis);
   run_command(argv);
   XMapWindow(dis, win);
   XCloseDisplay(dis);
   return 0;
}
