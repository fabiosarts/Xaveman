#include "WButton.hpp"

#include <X11/Xlib.h>

CWButton::CWButton(int posX, int posY, uint width, uint height, std::string label, CIconData *icon, CWidget *parent, XFontStruct *font)
    : CWidget(posX, posY, width, height, parent->getScreen(), parent->getDisplay(), parent->getWindow(), font)
{
    this->label = label;
    this->icon = icon;
}

CWButton::~CWButton()
{
}

void CWButton::Draw(Display *display, Drawable window, GC gc)
{
    // Draw the border
    XDrawRectangle(getDisplay(), getWindow(), gc, 0, 0, getWidth() - 1, getHeight() - 1);

    // Calculate text size and position
    int textWidth = XTextWidth(this->getFont(), this->label.c_str(), this->label.size());
    int textHeight = getFont()->ascent + getFont()->descent;
    int px = getWidth() / 2 - textWidth / 2;
    int py = getHeight() / 2 + textHeight / 2 - getFont()->descent;
    // TODO: I probably should cache these values to only recalculate them in resize events

    // Set the font and draw
    XSetFont(getDisplay(), gc, getFont()->fid);
    XDrawString(getDisplay(), getWindow(), gc, px, py, this->label.c_str(), label.size());
}
