#ifndef ICONS_H
#define ICONS_H

#include <X11/xpm.h>

#define ICONS_COUNT 6

#define ICON_FOLDER 0
#define ICON_FILE 1
#define ICON_SOCKET 2
#define ICON_BLOCK 3
#define ICON_CHARACTER 4
#define ICON_LINK 5

// Bitmap struct
class CIconData
{
private:
    Pixmap pixmap, mask;
    XpmAttributes attributes;
    bool init;

public:
    int Init(Display *display, Drawable window, char **image);
    int Draw(Display *display, Drawable window, GC gc, int pos_x, int pos_y);
    int Dispose(Display *display);
};

class CIconManager
{
private:
    CIconData icons[ICONS_COUNT];

protected:
    CIconManager();
    static CIconManager *instance;
    
    public:
    CIconManager(CIconManager &other) = delete;
    void operator=(const CIconManager&) = delete;
    static CIconManager *GetInstance();

    void Setup(Display *display, Drawable window);
    void DisposeAll(Display *display);
    CIconData *GetIcon(int iconType);
};

#endif