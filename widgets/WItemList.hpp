#ifndef WITEMLIST_HPP
#define WITEMLIST_HPP

#include <string>
#include <vector>
#include <X11/Xlib.h>

#include "Widget.hpp"
#include "../icons.hpp"

#define ITEMLIST_HEIGHT 20
#define ITEMLIST_ITEM_OFFSET 2
#define ITEMLIST_PADDING 5

class CWItemListEntry
{
private:
    CIconData *icon;
    CIconData *overlay;
    std::string label;
public:
    CWItemListEntry(CIconData *icon, CIconData *overlay, std::string label);
    CIconData *getIcon();
    CIconData *getOverlayIcon();
    std::string getLabel();
};

class CWItemList : public CWidget
{
private:
    std::vector<CWItemListEntry> items;
public:
    CWItemList(int x, int y, uint width, uint height, CWidget* parent, XFontStruct *font);
    ~CWItemList();
    
    // Add new item to the list
    void AddItem(CIconData *icon, CIconData *overlay, std::string label);
    // Clear the whole list
    void Clear();

    // Events
    void Draw(Display *display, Drawable window, GC gc) override;
    void onResize() override;
};


#endif // WITEMLIST_HPP
