#include "Widget.hpp"

CWidget::CWidget(int x, int y, uint width, uint height, int screen, Display *display, Window parent, XFontStruct *font)
{
    this->posX = x;
    this->posY = y;
    this->width = width;
    this->height = height;

    this->screen = screen;
    this->parent = parent;
    this->window = XCreateSimpleWindow(display, parent, x, y, width, height, 0, WhitePixel(display, screen), WhitePixel(display, screen));
    this->display = display;

    this->font = font;

    XMapWindow(display, this->window);
}

CWidget::~CWidget()
{
    for(CWidget* control: controls)
    {
        delete control;
    }
}

Display *CWidget::getDisplay()
{
    return this->display;
}

Window CWidget::getParent()
{
    return this->parent;
}

Window CWidget::getWindow()
{
    return this->window;
}

int CWidget::getScreen()
{
    return this->screen;
}

int CWidget::getPosX()
{
    return this->posX;
}

int CWidget::getPosY()
{
    return this->posY;
}

int CWidget::getWidth()
{
    return this->width;
}

int CWidget::getHeight()
{
    return this->height;
}

XFontStruct *CWidget::getFont()
{
    return this->font;
}

int CWidget::setRect(int posX, int posY, uint width, uint height)
{
    this->posX = posX;
    this->posY = posY;
    this->width = width;
    this->height = height;

    int result = XMoveResizeWindow(getDisplay(), getWindow(), posX, posY, width, height);
    XClearWindow(getDisplay(), getWindow());
    Draw(getDisplay(), getWindow(), DefaultGC(getDisplay(), getScreen()));

    this->onResize();
    return result;
}

void CWidget::AddControl(CWidget *widget)
{
    this->controls.push_back(widget);
}

void CWidget::Draw(Display *display, Drawable window, GC gc)
{
    for(CWidget* control: controls)
    {
        control->Draw(display, window, gc);
    }
}

void CWidget::onResize()
{
    for(CWidget* control: controls)
    {
        control->onResize();
    }
}
