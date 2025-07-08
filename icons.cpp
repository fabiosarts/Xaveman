#include "icons.hpp"

#include <cstdio>

#include "icons/folder.xpm"
#include "icons/file.xpm"
#include "icons/socket.xpm"
#include "icons/block.xpm"
#include "icons/character.xpm"
#include "icons/link.xpm"

CIconManager* CIconManager::instance = nullptr;

int CIconData::Init(Display *display, Drawable window, char **image)
{
    this->attributes.valuemask = 0;
    int result = XpmCreatePixmapFromData(display, window, image, &this->pixmap, &this->mask, &this->attributes);
    if (result != XpmSuccess)
    {
        printf("Error loading XPM!");
    }

    return result;
}

int CIconData::Draw(Display *display, Drawable window, GC gc, int pos_x, int pos_y)
{
    // Set the mask as a clip region
    XSetClipMask(display, gc, mask);
    XSetClipOrigin(display, gc, pos_x, pos_y);

    // Draw the pixmap using the GC
    XCopyArea(display, pixmap, window, gc,
              0, 0, this->attributes.width, this->attributes.height,
              pos_x, pos_y);

    // Remove the clip mask after drawing
    XSetClipMask(display, gc, None);

    return XpmSuccess;
}

int CIconData::Dispose(Display *display)
{
    {
        XFreePixmap(display, this->pixmap);
        if (this->mask)
            XFreePixmap(display, this->mask);
    }

    return 0;
}

void CIconManager::DisposeAll(Display *display)
{
    icons[ICON_FOLDER].Dispose(display);
    icons[ICON_FILE].Dispose(display);
    icons[ICON_SOCKET].Dispose(display);
    icons[ICON_BLOCK].Dispose(display);
    icons[ICON_CHARACTER].Dispose(display);
    icons[ICON_LINK].Dispose(display);
}

CIconManager::CIconManager()
{
    
}
CIconManager *CIconManager::GetInstance()
{
    if(instance == nullptr)
    {
        instance = new CIconManager();
    }

    return instance;
}
void CIconManager::Setup(Display *display, Drawable window)
{
    icons[ICON_FOLDER].Init(display, window, (char **)folder_xpm);
    icons[ICON_FILE].Init(display, window, (char **)file_xpm);
    icons[ICON_SOCKET].Init(display, window, (char **)socket_xpm);
    icons[ICON_BLOCK].Init(display, window, (char **)block_xpm);
    icons[ICON_CHARACTER].Init(display, window, (char **)character_xpm);
    icons[ICON_LINK].Init(display, window, (char**)link_xpm);
}

CIconData *CIconManager::GetIcon(int iconType)
{
    // Just in case
    if (iconType < 0 || iconType >= ICONS_COUNT)
    {
        return NULL;
    }

    return &(this->icons[iconType]);
}