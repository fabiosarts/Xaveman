#ifndef WBUTTON_HPP
#define WBUTTON_HPP

#include <string>
#include "Widget.hpp"
#include "../icons.hpp"

class CWButton : public CWidget
{
private:
    std::string label;
    CIconData *icon;

public:
    CWButton(int posX, int posY, uint width, uint height, std::string label, CIconData *icon, CWidget *parent, XFontStruct *font);
    ~CWButton();

    void Draw(Display *display, Drawable window, GC gc) override;
};

#endif // WBUTTON_HPP