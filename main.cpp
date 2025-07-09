#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <X11/xpm.h>
#include <cstdio>
#include <cstdlib>

#include "widgets/WMainApp.hpp"
#include "icons.hpp"

int main()
{
    // Open connection to X server
    Display *display = XOpenDisplay(NULL);
    if (display == NULL)
    {
        printf("Unable to open X display\n");
        exit(1);
    }

    // Get default screen
    int screen = DefaultScreen(display);

    // Create a simple window
    Window window = XCreateSimpleWindow(
        display,                     // Display
        RootWindow(display, screen), // Parent window (root)
        100, 100,                    // Position: x=100, y=100
        640, 480,                    // Size: width=640, height=480
        1,                           // Border width
        BlackPixel(display, screen), // Border color
        WhitePixel(display, screen)  // Background color
    );

    // Set window title
    XStoreName(display, window, "Xaveman");

    // Select kind of events we are interested in
    XSelectInput(display, window, ExposureMask | KeyPressMask | StructureNotifyMask);

    // Map (show) the window
    XMapWindow(display, window);

    // Prepare main font
    XFontStruct *font = XLoadQueryFont(display, "fixed");

    // Event Messages
    Atom wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, window, &wmDeleteMessage, 1);

    // Setup icons
    CIconManager::GetInstance()->Setup(display, window);

    // Caching main window width and height
    int oldWidth = 0;
    int oldHeight = 0;

    // WMainApp
    WMainApp *mainApp = new WMainApp(10, 10, 30, 60, screen, display, window, font);

    // Event loop
    bool running = true;
    while (running)
    {
        XEvent event;
        XNextEvent(display, &event); // Wait for next event

        switch (event.type)
        {
        case Expose:
            // Window exposed: redraw
            mainApp->Draw(display, window, DefaultGC(display, screen));
            break;

        case KeyPress:

            break;

        case DestroyNotify:
            printf("Destroyed!\n");
            // Window destroyed
            running = false;
            break;
        case ConfigureNotify:
            if (oldWidth != event.xconfigure.width || oldHeight != event.xconfigure.height)
            {
                mainApp->setRect(0, 0, event.xconfigure.width, event.xconfigure.height);

                oldWidth = event.xconfigure.width;
                oldHeight = event.xconfigure.height;
            }
            break;
        case ClientMessage:
            if ((Atom)event.xclient.data.l[0] == wmDeleteMessage)
            {
                running = false; // Exit the loop cleanly
            }
            break;
        }
    }

    // Cleanup
    CIconManager::GetInstance()->DisposeAll(display);
    delete mainApp;
    XDestroyWindow(display, window);
    XCloseDisplay(display);

    return 0;
}
