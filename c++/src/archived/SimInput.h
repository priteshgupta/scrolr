#ifndef SIMINPUT_H
#define SIMINPUT_H

#include <X11/Xlib.h>
#include <X11/keysym.h>

/*
 * This class is used to creating input
 */
class SimInput
{
public:
    int run();
    XKeyEvent createKeyEvent(Display *display, Window &win,
                           Window &winRoot, bool press,
                           int keycode, int modifiers);
};

#endif // SIMINPUT_H
