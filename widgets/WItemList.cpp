#include "WItemList.hpp"

#include "../icons.hpp"
#include <filesystem>

// CWItemListEntry item for CWItemList

CWItemListEntry::CWItemListEntry(CIconData *icon, CIconData *overlay, std::string label)
{
    this->icon = icon;
    this->overlay = overlay;
    this->label = label;
}

CIconData *CWItemListEntry::getIcon()
{
    return this->icon;
}

CIconData *CWItemListEntry::getOverlayIcon()
{
    return this->overlay;
}

std::string CWItemListEntry::getLabel()
{
    return this->label;
}

// CWItemList Widget definition

CWItemList::CWItemList(int x, int y, uint width, uint height, CWidget *parent, XFontStruct *font)
: CWidget(x, y, width, height, parent->getScreen(), parent->getDisplay(), parent->getWindow(), font)
{
    
}

CWItemList::~CWItemList()
{
}

void CWItemList::AddItem(CIconData *icon, CIconData *overlay, std::string label)
{
    items.push_back(CWItemListEntry(icon, overlay, label));
    
    // Clear and force redraw by calling manually
    XClearWindow(getDisplay(), getWindow());
    Draw(getDisplay(), getWindow(), DefaultGC(getDisplay(), getScreen()));
}

void CWItemList::Clear()
{
    items.clear();

    // Clear and force redraw by calling manually
    XClearWindow(getDisplay(), getWindow());
    Draw(getDisplay(), getWindow(), DefaultGC(getDisplay(), getScreen()));
}

void CWItemList::Draw(Display *display, Drawable window, GC gc)
{
    int width = getWidth() - ITEMLIST_PADDING * 2;
    int height = getHeight() - ITEMLIST_PADDING * 2;
    int offset_x = ITEMLIST_PADDING + 1; // 1 for the border
    int offset_y = ITEMLIST_PADDING + 1; // 1 for the border

    XDrawRectangle(getDisplay(), getWindow(), gc, 0, 0, getWidth() - 1, getHeight() - 1);

    int displayCapacity = height / ITEMLIST_HEIGHT;

    for(int i=0; i < items.size() && i < displayCapacity; i++)
    {
        CWItemListEntry *entry = &items.at(i);

        // Draw the regular icon
        entry->getIcon()->Draw(getDisplay(), getWindow(), gc, 
        offset_x,
        offset_y + i * ITEMLIST_HEIGHT + ITEMLIST_ITEM_OFFSET);

        // Draw the overlay icon (if any)
        if(entry->getOverlayIcon() != nullptr)
        {
            entry->getOverlayIcon()->Draw(getDisplay(), getWindow(), gc, 
            offset_x,
            offset_y + i * ITEMLIST_HEIGHT + ITEMLIST_ITEM_OFFSET);
        }

        XDrawString(getDisplay(), getWindow(), gc, 
        offset_x + 16 + 4,
        i * ITEMLIST_HEIGHT + ITEMLIST_HEIGHT,
        entry->getLabel().c_str(), entry->getLabel().length());
    }
}

void CWItemList::onResize()
{
}
