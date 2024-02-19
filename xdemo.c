// gcc -g -o xdemo xdemo.c -lX11
#include <string.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>

int main(int argc, char *argv[]) {
    Display *display = XOpenDisplay(NULL);
    int screen = DefaultScreen(display);
    int width = DisplayWidth(display, screen)/2;
    int height = DisplayHeight(display, screen)/2;

    Window win = XCreateSimpleWindow(display, RootWindow(display, screen)
        , 0,  0, width, height, 3, BlackPixel(display, screen), WhitePixel(display, screen));
    XSelectInput(display, win, ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask);

    GC gc = XCreateGC(display, win, 0, NULL);

    XMapWindow(display, win);

    while(1) {
        XEvent event = {0};
        XNextEvent(display, &event);

        switch(event.type) {
        case ConfigureNotify:
            width = event.xconfigure.width;
            height = event.xconfigure.height;
            break;
        case Expose:
            XSetForeground(display, gc, WhitePixel(display, screen));
            XFillRectangle(display, win, gc, 0, 0, width, height);
            XSetForeground(display, gc, BlackPixel(display, screen));
            XDrawString(display, win, gc, width/2, height/2, "XWindow", 7);
            break;
        case KeyPress:
            if(event.xkey.keycode == XKeysymToKeycode(display, XK_Escape)) {
                XFreeGC(display, gc);
                XCloseDisplay(display);
                return 0;
            }
        default:
            break;
        }
    }

    return 0;
}

