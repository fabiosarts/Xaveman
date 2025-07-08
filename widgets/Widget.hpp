#ifndef WIDGET_HPP
#define WIDGET_HPP
#include <vector>

#include <X11/Xlib.h>

class CWidget
{
private:
    int screen;
    Window parent;
    Window window;
    Display *display;
    int posX, posY;
    int width, height;
    std::vector<CWidget *> controls;

public:
    // Constructor
    CWidget(int x, int y, uint width, uint height, int screen, Display *display, Window parent);
    virtual ~CWidget();

    //static CWidget* Create(CWidget* parent, int posX, int posY, uint width, uint height);

    Display *getDisplay();
    Window getParent();
    Window getWindow();

    int getScreen();
    int getPosX();
    int getPosY();
    int getWidth();
    int getHeight();

    int setRect(int posX, int posY, uint width, uint height);

    void AddControl(CWidget *widget);
    
    // Events
    virtual void Draw(Display *display, Drawable window, GC gc);
    virtual void onResize();
};

#endif // WIDGET_HPP
